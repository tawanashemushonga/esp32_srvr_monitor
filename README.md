# ESP32 Server Room Temperature & Humidity Monitor

**Author**: Tawanashe E. Mushonga  
**Discipline**: Electronics & Telecommunications Engineering  
**Hardware**: ESP32 Dev Module + DHT11  
**Cloud**: [ThingSpeak](https://thingspeak.com/)

---

## 📖 Project Overview

This IoT project monitors the temperature and humidity in a server room using an **ESP32** and **DHT11 sensor**. Readings are published to a ThingSpeak channel every 20 seconds, and alerts are generated when temperatures fall outside the safe range.

---

## 🛠️ Hardware Components

| Component       | Quantity | Description                        |
|---------------- |----------|------------------------------------|
| ESP32 Dev Board | 1        | Microcontroller with WiFi          |
| DHT11 Sensor    | 1        | Temperature & Humidity Sensor      |
| Jumper Wires    | Few      | For connections                    |
| Breadboard      | Optional | For prototyping                    |

---

## 🔌 Wiring Diagram

| DHT11 Pin | ESP32 Pin |
|-----------|-----------|
| VCC       | 3.3V      |
| GND       | GND       |
| DATA      | GPIO 4    |

---

## 🌐 ThingSpeak Setup

1. Create an account at [ThingSpeak](https://thingspeak.com/)
2. Create a new channel with 3 fields:
   - **Field 1**: Temperature (°C)
   - **Field 2**: Humidity (%)
   - **Field 3**: Status Code (0 = Too Low, 1 = Normal, 2 = Too High)
3. Copy your **Channel ID** and **Write API Key**
4. Paste them into the Arduino code

---

## 💻 Arduino Code

See `server_room_monitor.ino` in this repository.

> Remember to install the following libraries in Arduino IDE:  
> - `DHT sensor library` by Adafruit  
> - `ThingSpeak` by MathWorks  
> - `WiFi` (already available for ESP32 boards)

---

## 📊 ThingSpeak Channel Example

![ThingSpeak Screenshot](images/thingspeak.png)

---

## 🚨 Alert System

The program checks if the temperature is within safe limits:
- **Below 18°C** → Alert: "TOO LOW"
- **18°C - 27°C** → Status: Normal
- **Above 27°C** → Alert: "TOO HIGH"

---

## ✅ Future Improvements

- Add email/SMS alerts using IFTTT or Twilio
- Add LCD or OLED display
- Add push-button to reset alerts
- Use DHT22 for better accuracy

---

## 🧠 Author Info

> Tawanashe E. Mushonga  
> Electronics & Telecommunications Engineering Student  
> Passionate about embedded systems, IoT, and automation.

---

## 📄 License

This project is open-source under the MIT License.

