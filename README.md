# Air Quality Monitoring System  
**Real-Time Gas Detection & Cloud-Based Air Quality Tracking**

## 📌 Overview

This project presents an intelligent IoT-based Air Quality Monitoring System using an ESP32 and an MQ-135 gas sensor. Unlike basic pollution detectors that only show local readings, this solution continuously uploads data to ThingSpeak cloud, provides threshold-based alerts, and enables remote monitoring of harmful gases such as CO₂, NH₃, benzene, smoke, and NOₓ.

## 🎯 Objectives

- Continuously measure air quality (harmful gas concentration)
- Upload real-time data to ThingSpeak cloud dashboard
- Trigger local alerts when air quality degrades
- Enable low-cost, scalable remote environmental monitoring
- Provide data logging for long-term pollution trend analysis

## ⚙️ System Working

- The MQ-135 gas sensor detects gas concentration and outputs an analog voltage.
- The ESP32 reads this voltage on GPIO34 and converts it to a raw ADC value (0–4095).
- Every 15 seconds, the ESP32 sends the value to ThingSpeak via Wi-Fi.
- The system compares the reading against a preset threshold (e.g., 2000).
- If the threshold is exceeded, a “Poor Air Quality” alert is printed on the serial monitor.
- Users can view live graphs and historical data on the ThingSpeak dashboard from anywhere.

## 🏆 Innovation & Advanced Features

###  Real-Time Cloud Dashboard

Unlike standalone detectors, this system pushes data to the cloud, allowing remote monitoring and data logging without physical presence.

###  Threshold-Based Smart Alerting

The system instantly classifies air as “Good” or “Poor” and can be extended to trigger LEDs, buzzers, or notifications.

###  IoT-Enabled Data Logging

All readings are stored on ThingSpeak, enabling long-term trend analysis, pollution pattern detection, and decision-making for health and safety.

###  Low-Cost & Scalable

Built with affordable components (ESP32 + MQ-135), the system can be deployed indoors, outdoors, or across multiple locations.

###  Visual Analytics

ThingSpeak provides graphs, gauges, and widgets to visualize air quality changes over minutes, hours, or days.

## 🧰 Components Used

- ESP32 DevKit V1
- MQ-135 Gas Sensor
- Jumper Wires
- Breadboard
- 5V USB Power Supply
- Wi-Fi network

## 💡 Key Features

- Real-time air quality measurement
- Automatic cloud upload (ThingSpeak)
- Local threshold-based air quality classification
- Remote access from any device
- Data logging and graphing
- Easy to replicate and scale

## 🔌 Wiring & Connections

| MQ-135 Pin | ESP32 Pin |
|------------|-----------|
| VCC        | 5V / VIN  |
| GND        | GND       |
| AOUT       | GPIO34    |

## 💻 Code Logic (Arduino)

- Initialize Wi-Fi and ThingSpeak
- Read analog value from GPIO34
- Compare with threshold and print status
- Send value to ThingSpeak field every 15 seconds
- Handle Wi-Fi reconnection automatically

## 🧪 Simulation & Testing

The system logic was tested on a physical ESP32 with MQ-135 sensor.  
Serial monitor output and ThingSpeak dashboard were used to verify data transmission and alert accuracy.

## 🎥 working

<img width="1600" height="1204" alt="WhatsApp Image 2026-04-15 at 11 37 03 PM" src="https://github.com/user-attachments/assets/cd50ac10-2aaf-42ae-bc14-91ce8a20b425" />
<img width="888" height="648" alt="WhatsApp Image 2026-04-15 at 11 35 38 PM" src="https://github.com/user-attachments/assets/18684ea1-6e9a-4ea4-9e23-9d9ee70b7a65" />
<img width="1600" height="654" alt="WhatsApp Image 2026-04-15 at 11 35 38 PM (1)" src="https://github.com/user-attachments/assets/737e313a-96c7-453b-b61d-9af610d7b2e1" />


## 🚀 Future Enhancements

- Add a local LCD display for instant readings
- Integrate Blynk or Telegram for push notifications
- Convert raw ADC to PPM using calibration formulas
- Add multiple sensors (PM2.5, CO, etc.)
- Implement solar power for remote deployment
- Use MQTT instead of HTTP for faster updates

## 🏅 Innovation Statement

> “Unlike conventional air quality monitors that only display local readings, our solution provides real-time cloud-based tracking, threshold-based alerts, and historical data logging—making air pollution monitoring intelligent, remote, and data-driven.”

## 👩‍💻 Author

- **Lakshmipriya K G** (MGP24EVLSI017)   

**Course:** Semester 3, Electronics Engineering (VLSI Design and Technology)  
**Institution:** Saintgits College of Engineering

