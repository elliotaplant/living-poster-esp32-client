#include <WiFiClient.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <config.h>

// Returns the server time that the conditions were sent at
Conditions requestConditions(
  String dataUrl,
  String beach,
  String posterId,
  String batteryVoltage) {
  Conditions conditions = { 0, false, { 0, 0, 0 } };

  String combinedUrl = dataUrl;
  combinedUrl += String("?beach=");
  combinedUrl += beach;
  combinedUrl += String("&poster_id=");
  combinedUrl += posterId;
  combinedUrl += String("&millis=");
  combinedUrl += String(millis());
  combinedUrl += String("&battery=");
  combinedUrl += String(batteryVoltage);

  Serial.println("Connecting to domain:");
  Serial.println(combinedUrl);

  // Create an HTTPClient instance
  HTTPClient http;

  // Initializing an HTTP communication using insecure client
  Serial.println("[HTTP] begin...");
  if (http.begin(combinedUrl)) {
    Serial.println("[HTTP] GET...");
    // Start connection and send HTTP header
    int httpCode = http.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] Code: %d\n", httpCode);
      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        // Parse the response as JSON
        DynamicJsonDocument doc(2048);
        DeserializationError error = deserializeJson(doc, http.getStream());

        if (error) {
          Serial.print(F("deserializeJson() failed: "));  // What the F do?
          Serial.println(error.f_str());
        } else {

          double time = doc["time"];
          conditions.timeMs = time;
          conditions.valid = true;
          for (int i = 0; i < NUM_DIALS; i++) {
            Dial dial = DIALS[i];
            conditions.values[i] = doc["conditions"][dial.key];
          }
        }
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }

  return conditions;
}