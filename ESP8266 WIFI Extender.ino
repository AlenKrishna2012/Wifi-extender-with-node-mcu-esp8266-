#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

extern "C" {
  #include "lwip/napt.h"
  #include "lwip/err.h"
}

/* ========= LED PINS ========= */
#define POWER_LED 2
#define CONN_LED  16

/* ========= OBJECTS ========= */
AsyncWebServer server(80);

/* ========= GLOBALS ========= */
String ssidList = "";
unsigned long lastScan = 0;
bool wifiConnected = false;

/* ========= HTML ========= */
String webPage() {
  return R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP NAT Extender</title>

<style>
body{font-family:Arial;background:#f2f2f2;text-align:center;}
.box{background:#fff;padding:20px;margin:30px auto;max-width:360px;border-radius:10px;}
select,input,button{width:90%;padding:10px;margin:10px;font-size:16px;}
button{border:none;border-radius:6px;color:white;}
.connect{background:#4CAF50;}
.reset{background:#f44336;}
</style>

<script>
function updateSSID(){
  fetch('/scan')
    .then(r => r.text())
    .then(d => {
      document.getElementById('ssid').innerHTML = d;
    });
}
setInterval(updateSSID, 5000);
window.onload = updateSSID;
</script>

</head>
<body>
<div class="box">
<h2>ESP8266 NAT Extender</h2>

<form action="/connect">
<select id="ssid" name="ssid"></select>
<input type="password" name="pass" placeholder="WiFi Password">
<button class="connect">Connect</button>
</form>

<form action="/reset">
<button class="reset">Reset WiFi</button>
</form>
</div>
</body>
</html>
)rawliteral";
}

/* ========= WIFI SCAN ========= */
void scanWiFi() {
  int n = WiFi.scanNetworks(false, true);
  ssidList = "";
  for (int i = 0; i < n; i++) {
    ssidList += "<option value=\"" + WiFi.SSID(i) + "\">";
    ssidList += WiFi.SSID(i);
    ssidList += " (" + String(WiFi.RSSI(i)) + "dBm)";
    ssidList += "</option>";
  }
  WiFi.scanDelete();
}

/* ========= SPIFFS ========= */
void saveCred(String s, String p) {
  File f = LittleFS.open("/wifi.txt", "w");
  if (f) { f.println(s); f.println(p); f.close(); }
}

bool loadCred(String &s, String &p) {
  if (!LittleFS.exists("/wifi.txt")) return false;
  File f = LittleFS.open("/wifi.txt", "r");
  if (!f) return false;
  s = f.readStringUntil('\n'); s.trim();
  p = f.readStringUntil('\n'); p.trim();
  f.close();
  return true;
}

/* ========= CONNECT ========= */
void connectWiFi(String ssid, String pass) {
  WiFi.begin(ssid.c_str(), pass.c_str());
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 20000) {
    digitalWrite(CONN_LED, !digitalRead(CONN_LED));
    delay(300);
  }

  wifiConnected = (WiFi.status() == WL_CONNECTED);
  digitalWrite(CONN_LED, wifiConnected ? LOW : HIGH);

  if (wifiConnected) {
    ip_napt_enable_no(SOFTAP_IF, 1);   // 🔥 ENABLE NAT
  }
}

/* ========= SETUP ========= */
void setup() {
  Serial.begin(115200);

  pinMode(POWER_LED, OUTPUT);
  pinMode(CONN_LED, OUTPUT);
  digitalWrite(POWER_LED, LOW);
  digitalWrite(CONN_LED, HIGH);

  LittleFS.begin();

  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.mode(WIFI_AP_STA);

  WiFi.softAP("ESP_NAT_Extender", "12345678");
  Serial.println(WiFi.softAPIP());

  String s, p;
  if (loadCred(s, p)) connectWiFi(s, p);

  scanWiFi();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *r){
    r->send(200, "text/html", webPage());
  });

  server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *r){
    r->send(200, "text/plain", ssidList);
  });

  server.on("/connect", HTTP_GET, [](AsyncWebServerRequest *r){
    if (r->hasParam("ssid") && r->hasParam("pass")) {
      String s = r->getParam("ssid")->value();
      String p = r->getParam("pass")->value();
      saveCred(s, p);
      connectWiFi(s, p);
    }
    r->redirect("/");
  });

  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *r){
    LittleFS.remove("/wifi.txt");
    r->send(200, "text/html", "<h3>Resetting…</h3>");
    delay(1500);
    ESP.restart();
  });

  server.begin();
}

/* ========= LOOP ========= */
void loop() {
  if (millis() - lastScan > 5000) {
    lastScan = millis();
    scanWiFi();
  }

  if (!wifiConnected) {
    digitalWrite(CONN_LED, millis() / 500 % 2);
  }
}