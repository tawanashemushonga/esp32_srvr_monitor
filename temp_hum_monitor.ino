/*
  Project: Server Room Temperature & Humidity Monitor with Alerts
  Description: This code reads data from a DHT11 sensor, posts it to a ThingSpeak channel,
               and sends a status code if the temperature is outside the normal range.
  Board: ESP32 Dev Module
  Sensor: DHT11
  Author: Tawanashe E Mushonga (Electronics & Telecom Engineer)
*/

// Include necessary libraries
#include <WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"

// --- WiFi Credentials ---
// Replace with your network SSID (name) and password
const char* SECRET_SSID = "MedWireless";
const char* SECRET_PASS = "ttt048680#";

// --- ThingSpeak Configuration ---
// Replace with your Channel ID and Write API Key
unsigned long myChannelNumber = 3002894; // Your Channel ID
const char * myWriteAPIKey = "OIFZ6TR8PXIALIPM"; // Your Write API Key

// --- DHT Sensor Configuration ---
#define DHTPIN 4       // The GPIO pin connected to the DHT11 data pin
#define DHTTYPE DHT11  // Define the type of DHT sensor being used

// --- Alert Configuration ---
// Define the normal operating temperature range for your server room (in Celsius)
const float TEMP_NORMAL_MAX = 27.0;
const float TEMP_NORMAL_MIN = 18.0;

// Initialize DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

// Initialize WiFi client library
WiFiClient client;

// --- Main Program ---

void setup() {
  // Start serial communication for debugging purposes
  Serial.begin(115200);
  Serial.println("Server Room Monitor - Starting up...");

  // Initialize the DHT sensor
  dht.begin();
  
  // Initialize ThingSpeak communication
  ThingSpeak.begin(client);

  // Connect to WiFi
  connectToWiFi();
}

void loop() {
  // ThingSpeak requires a delay of at least 15 seconds between updates.
  // We'll wait 20 seconds to be safe.
  delay(20000); 

  // Check WiFi connection status. If not connected, try to reconnect.
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Trying to reconnect...");
    connectToWiFi();
  }

  // Read temperature and humidity from the DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early to try again.
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return; // Exit the loop and try again on the next iteration
  }

  // Print the readings to the Serial Monitor for local debugging
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, ");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // --- Check Temperature and Set Status ---
  // Status Codes:
  // 1 = Normal
  // 2 = Temperature Too High
  // 0 = Temperature Too Low
  int tempStatus = 1; // Default to Normal

  if (temperature > TEMP_NORMAL_MAX) {
    tempStatus = 2; // Temperature is too high
    Serial.println("ALERT: Temperature is TOO HIGH!");
  } else if (temperature < TEMP_NORMAL_MIN) {
    tempStatus = 0; // Temperature is too low
    Serial.println("ALERT: Temperature is TOO LOW!");
  } else {
    Serial.println("Status: Temperature is Normal.");
  }

  // Set the fields with the sensor data and status
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, tempStatus); // Send the status code to Field 3

  // Write the fields to the ThingSpeak channel
  int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if (httpCode == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(httpCode));
  }
}

// --- Helper Functions ---

void connectToWiFi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(SECRET_SSID);

  WiFi.mode(WIFI_STA); // Set WiFi to station mode
  WiFi.begin(SECRET_SSID, SECRET_PASS);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

