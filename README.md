# simple and affordable air quality monitor
# Air Quality Monitoring System with ESP32 & MQ-135

![ESP32](https://img.shields.io/badge/ESP32-ThingSpeak-blue) ![Air Quality](https://img.shields.io/badge/Air%20Quality-MQ135-green) ![License](https://img.shields.io/badge/License-MIT-yellow)

## 📌 Overview

This project implements a **real-time air quality monitoring system** using an ESP32 DevKit V1 and an MQ-135 gas sensor. It reads the concentration of harmful gases (CO₂, NH₃, benzene, smoke, NOₓ) and sends the raw ADC value to **ThingSpeak** cloud platform. The system also provides a local threshold alert on the Serial Monitor.

> **Note:** The current version uses raw ADC values (0–4095).

---

## 🎯 Features

- Reads analog signal from MQ-135 sensor on GPIO34.
- Connects to Wi-Fi and uploads data to ThingSpeak every 15 seconds.
- Compares sensor value against a threshold (2000) and prints air quality status.
- Low-cost, easy to replicate.

---

## 🧰 Components Required

| Component               | Quantity |
|------------------------|----------|
| ESP32 DevKit V1        | 1        |
| MQ-135 Gas Sensor      | 1        |
| Jumper Wires (F/F or F/M) | As needed |
| Breadboard             | 1        |
| USB cable (for power & programming) | 1 |

---

## 🔌 Wiring Diagram

| MQ-135 Pin | ESP32 Pin         |
|------------|-------------------|
| VCC        | 5V / VIN          |
| GND        | GND               |
| AOUT       | GPIO34 (ADC1_CH6) |

> **Note:** The MQ-135 requires a 5V supply. ESP32's VIN pin works when powered via USB.

---

## 📡 ThingSpeak Setup

1. Create a free account at [ThingSpeak.com](https://thingspeak.com).
2. Create a new channel with **Field 1** named `Air Quality (ADC)`.
3. Note your **Channel ID** and **Write API Key**.

---

## 💻 Code (AirQualitySystem.ino)

The complete code is shown below. Replace the Wi-Fi credentials and ThingSpeak keys with your own.

```cpp
#include <WiFi.h>
#include <ThingSpeak.h>

// --- PIN DEFINITIONS ---
#define MQ135_PIN 34          // MQ-135 Analog Output

// --- THRESHOLD (raw ADC value, 0-4095) ---
#define SENSOR_THRESHOLD 2000 // Adjust based on your environment

// --- WiFi Credentials ---
const char* ssid     = "YOUR_SSID";       // Replace with your Wi-Fi SSID
const char* password = "YOUR_PASSWORD";   // Replace with your Wi-Fi password

// --- ThingSpeak Settings ---
unsigned long channelID = 1234567;        // Your channel ID
const char* writeAPKey  = "YOUR_API_KEY"; // Your Write API Key

WiFiClient client;
unsigned long lastThingSpeakUpdate = 0;

void setup() {
  Serial.begin(115200);
  pinMode(MQ135_PIN, INPUT);
  
  Serial.println("Air Quality Monitoring System Starting...");
  Serial.println("Waiting 2 minutes for MQ-135 sensor to warm up.");
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

void loop() {
  // Read sensor (raw ADC value)
  int sensorValue = analogRead(MQ135_PIN);
  Serial.print("Air Quality (Raw ADC): ");
  Serial.println(sensorValue);

  // Threshold check
  if (sensorValue > SENSOR_THRESHOLD) {
    Serial.println("⚠️ Poor Air Quality Detected!");
  } else {
    Serial.println("✅ Air Quality is Good.");
  }

  // Send to ThingSpeak every 15 seconds
  if (millis() - lastThingSpeakUpdate > 15000) {
    lastThingSpeakUpdate = millis();

    if (WiFi.status() == WL_CONNECTED) {
      ThingSpeak.setField(1, sensorValue);
      int response = ThingSpeak.writeFields(channelID, writeAPKey);
      if (response == 200) {
        Serial.println("📡 ThingSpeak Updated Successfully");
      } else {
        Serial.print("❌ ThingSpeak update failed, code: ");
        Serial.println(response);
      }
    } else {
      Serial.println("WiFi not connected, cannot update ThingSpeak");
    }
  }
  
  delay(1000); // Small delay before next reading
}
