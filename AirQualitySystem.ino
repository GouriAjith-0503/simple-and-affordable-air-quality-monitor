#include <WiFi.h>
#include <ThingSpeak.h>

// ---------- PIN DEFINITIONS ----------
#define MQ135_PIN 34    // MQ-135 Analog Output Pin (GPIO34)

// ---------- THRESHOLD ----------
#define SENSOR_THRESHOLD 2000  // Example threshold for ADC reading (0-4095)

// ---------- WiFi & ThingSpeak ----------
const char* ssid = "Redmi 12 5G";
const char* password = "p7fqp754nhamiy6";

unsigned long channelID = 3334454; // Replace with your ThingSpeak channel ID
const char* writeAPIKey = "XI72PMC80QWKIH4I"; // Replace with your ThingSpeak Write API key

WiFiClient client;
unsigned long lastThingSpeakUpdate = 0;

void setup() {
  Serial.begin(115200);

  // Initialize Pins
  pinMode(MQ135_PIN, INPUT);

  Serial.println("🌱 Air Quality Monitoring System Starting...");
  Serial.println("Waiting 2 minutes for sensor warm-up...");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

void loop() {
  // ----- MQ-135 SENSOR READING -----
  int sensorValue = analogRead(MQ135_PIN);
  Serial.print("☁️ Air Quality (Raw ADC Value): ");
  Serial.println(sensorValue);

  // Threshold Comparison
  if (sensorValue > SENSOR_THRESHOLD) {
    Serial.println("⚠️ Poor Air Quality Detected!");
  } else {
    Serial.println("✅ Air Quality is Good.");
  }
  Serial.println("-----------------------------");

  // ----- ThingSpeak update every 15 sec -----
  if (millis() - lastThingSpeakUpdate > 15000) {
    lastThingSpeakUpdate = millis();

    if (WiFi.status() == WL_CONNECTED) {
      // Set the field value (Field 1)
      ThingSpeak.setField(1, sensorValue);

      // Write data to ThingSpeak
      int response = ThingSpeak.writeFields(channelID, writeAPIKey);
      if (response == 200) {
        Serial.println("✅ ThingSpeak Updated Successfully");
      } else {
        Serial.print("❌ ThingSpeak update failed, code: ");
        Serial.println(response);
      }
    } else {
      Serial.println("❌ WiFi not connected, cannot update ThingSpeak");
    }
  }

  delay(2000); // Print values locally every 2 seconds+
}
