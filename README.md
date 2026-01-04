# 🚀 ESP8266 Wi-Fi NAT Extender with Web Configuration

Turn an ESP8266 into a **real Wi-Fi extender / mini router** with **NAT**, **web-based setup**, **auto Wi-Fi scanning**, and **credential storage**.

✔ Works on most ESP8266 models  
✔ True routing — not just repeating

---

## 📸 Screenshots

### 🔹 Web Configuration Page
![Web UI](https://github.com/user-attachments/assets/8ee8f5e3-1e11-46de-9115-8d183c8a098c)

### 🔹 SSID Auto-Scan Dropdown
![SSID Scan](https://github.com/user-attachments/assets/1707fe18-d4ce-4539-9cb8-765555ca1baf)

---

## 📡 What This Project Does

This project converts an **ESP8266 (NodeMCU)** into a **true NAT-based Wi-Fi extender**:

- ESP8266 creates its own **Wi-Fi Access Point (AP)**
- ESP8266 connects to an existing router (**STA mode**)
- **NAT (lwIP NAPT)** routes traffic between AP ↔ STA
- Connected clients receive **real internet access**
- Configuration is done via a **web interface**

This is **not just a repeater** — it performs **real routing** like a mini router.

---

## ✨ Features

- Real NAT (lwIP NAPT)
- AP + STA mode simultaneously
- Web-based configuration
- Auto Wi-Fi scanning every 5 seconds
- SSID dropdown selection
- Password input
- Credentials saved in **LittleFS**
- Web reset (clears saved Wi-Fi)
- LED status indicators
- Works like a **mini router**

---

## 🌐 Default Network Settings

- **AP SSID:** `ESP_NAT_Extender`
- **AP Password:** `12345678`
- **AP IP Address:** `192.168.4.1`
- **Web UI:** http://192.168.4.1

---

## 🖥️ Web Interface Features

- Automatically scans nearby Wi-Fi networks
- SSID list refreshes every **5 seconds**
- Select SSID from dropdown
- Enter Wi-Fi password
- Connect to upstream router
- Reset saved credentials from the web
- No reboot required for scanning

---

## 💾 File System (LittleFS)

Wi-Fi credentials are stored in:
/wifi.txt

### File Format
SSID PASSWORD

---

## 🔄 Reset Button

- Deletes `/wifi.txt`
- Reboots the ESP8266
- Restarts in **fresh AP mode**

---

## 💡 LED Indications

- **Power LED ON** → Device powered and running
- **Connection LED BLINKING** → Scanning or connecting
- **Connection LED SOLID ON** → Connected, NAT active
- **Long blinking** → Wrong password or failed connection
- **Web reset** → LEDs briefly OFF, device restarts

⚠️ Built-in LED logic may be inverted on some boards.

---

## 🔧 Hardware Required

- ESP8266 (NodeMCU / ESP-12E / ESP-12F)
- USB cable
- Stable 5V power supply
- Optional LEDs + resistors

---

## ⚙️ Arduino IDE Settings (IMPORTANT)
Board           : NodeMCU 1.0 (ESP-12E Module) CPU Frequency   : 80 MHz Flash Size      : 4MB Flash Mode      : DIO LWIP Variant    : v2 Higher Bandwidth Upload Speed    : 115200

⚠️ Do NOT use `v2 Higher Bandwidth (no features)` — NAT will not work.

---

## 📦 Required Libraries

- ESP8266WiFi
- ESPAsyncWebServer
- AsyncTCP
- LittleFS
- DNSServer

NAT (lwIP NAPT) is included in the ESP8266 core.

---

## 🚀 How to Use

1. Flash the code to ESP8266
2. Power on the device
3. Connect to Wi-Fi  
   **SSID:** `ESP_NAT_Extender`  
   **Password:** `12345678`
4. Open browser and go to  
   http://192.168.4.1
5. Select SSID
6. Enter password
7. Click **Connect**
8. Wait for LED to turn solid

🎉 You now have internet through the ESP8266!

---

## 📈 Performance

- Typical speed: **15–25 Mbps**
- Depends on signal quality
- Suitable for browsing, IoT, light streaming

---

## ⚠️ Limitations

- Limited RAM (ESP8266)
- Not suitable for heavy traffic
- No WPA2-Enterprise
- No advanced firewall rules

---

## 👤 Author

**Alen Krishna V.U**

---

## 🔗 My Other Repositories

I have projects related to Python and Arduino ect

Visit my **GitHub profile** to explore more.
Click here👇
https://github.com/AlenKrishna2012
