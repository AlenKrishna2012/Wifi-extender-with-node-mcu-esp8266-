# ****ESP8266 Wi-Fi NAT Extender with Web Configuration****

Turn an ESP8266 into a real Wi-Fi extender / mini router with NAT, web-based setup, auto Wi-Fi scanning, and credential storage.

## Screenshots

🔹 Web Configuration Page
![Image](https://github.com/user-attachments/assets/8ee8f5e3-1e11-46de-9115-8d183c8a098c)
🔹 SSID Auto Scan Dropdown
![Image](https://github.com/user-attachments/assets/1707fe18-d4ce-4539-9cb8-765555ca1baf)

## 📡 What This Project Does

### This project converts an ESP8266 (NodeMCU) into a real NAT-based Wi-Fi extender:

ESP8266 creates its own Wi-Fi Access Point (AP)

ESP8266 connects to an existing router (STA)

NAT routes traffic between AP ↔ STA

Clients get real internet access

A web interface is used for setup

This is not just a repeater — it performs true routing.

## ✨ Features
✅ Real NAT (lwIP NAPT)

✅ AP + STA mode simultaneously

✅ Web-based configuration

✅ Auto Wi-Fi scanning every 5 seconds

✅ SSID dropdown selection

✅ Password input

✅ Credentials saved in LittleFS

✅ Web reset (clears saved Wi-Fi)

✅ LED status indicators

✅ Works like a mini router

## 🌐 Default Network Settings

AP SSID:**ESP_NAT_Extender**

AP Password:**12345678**

AP IP Address:**192.168.4.1**

Web UI:**http://192.168.4.1**

## 🖥️ Web Interface Features
Automatically scans nearby Wi-Fi networks

SSID list refreshes every 5 seconds

Select SSID from dropdown

Enter Wi-Fi password

Connect to upstream router

Reset saved credentials via web

No reboot required for scanning.
## 💾 File System (LittleFS)
Wi-Fi credentials are stored in:
***/wifi.txt***
### Format:

SSID

PASSWORD
## 🔄 Reset Button
Deletes /wifi.txt and Reboots ESP then starts fresh AP mode

## 💡 LED Indications
The **Power LED turns ON** as soon as the ESP8266 is powered, indicating that the device is receiving power and has started successfully.

The **Connection LED blinks continuously** while the ESP8266 is scanning for available Wi-Fi networks or trying to connect to the selected Wi-Fi network.

The **Connection LED turns ON (steady)** when the ESP8266 successfully connects to the target Wi-Fi network and internet routing is active.

If **the Connection LED keeps blinking for a long time**, it indicates that the Wi-Fi connection has failed or the entered password is incorrect.

When the device is reset from the web interface, **both LEDs briefly turn OFF**, and the ESP8266 restarts to factory Wi-Fi settings.
### ⚠️ Built-in LED logic may be inverted on some boards.


## 🔧 Hardware Required
ESP8266 (NodeMCU / ESP-12E / ESP-12F)

USB cable

Stable 5V power supply

Optional LEDs + resistors

## ⚙️ Arduino IDE Settings (IMPORTANT)
### Correct settings are critical for NAT to work.
Copy code

Board           : NodeMCU 1.0 (ESP-12E Module)
CPU Frequency   : 160 MHz
Flash Size      : 4MB
Flash Mode      : DIO
LWIP Variant    : v2 Higher Bandwidth
Upload Speed    : 921600 (or 115200 if unstable)

## 📦 Required Libraries

Install via Arduino Library Manager:

ESP8266WiFi

ESPAsyncWebServer

AsyncTCP

LittleFS

DNSServer

NAT (lwIP NAPT) is included in the ESP8266 core.

## 🚀 How to Use
Flash the code to ESP8266

Power on the device

Connect to Wi-Fi:

**ESP_NAT_Extender**

Open browser:

search:**http://192.168.4.1**

Select SSID

Enter password

Click Connect

Wait for connection LED to turn solid

**🎉 You now have internet through the ESP8266!**

## 📈 Performance
Typical speed: 15–25 Mbps

Depends on signal quality & router

Suitable for browsing, IoT, light streaming

## ⚠️ Limitations

Limited RAM (ESP8266)

Not suitable for heavy traffic

No WPA2-Enterprise

No advanced firewall rules
