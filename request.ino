#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <config.h>

// Returns the server time that the conditions were sent at
Conditions requestConditions(
    String dataUrl,
    String beach,
    String posterId,
    String batteryVoltage)
{
  Conditions conditions = {0, {0, 0, 0}};

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

  // Use WiFiClient class to create TCP connections
  WiFiClientSecure *client = new WiFiClientSecure;
  if (client)
  {
    // Not using an SSL cert because there's no secret info
    client->setInsecure();

    // Create an HTTPClient instance
    HTTPClient https;

    // Initializing an HTTPS communication using the secure client
    Serial.println("[HTTPS] begin...");
    if (https.begin(*client, combinedUrl.c_str()))
    {
      Serial.println("[HTTPS] GET...");
      // Start connection and send HTTP header
      int httpCode = https.GET();
      // httpCode will be negative on error
      if (httpCode > 0)
      {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] Code: %d\n", httpCode);
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
          // Parse the response as JSON
          DynamicJsonDocument doc(2048);
          DeserializationError error = deserializeJson(doc, https.getStream());

          if (error)
          {
            Serial.print(F("deserializeJson() failed: ")); // What the F do?
            Serial.println(error.f_str());
          }
          else
          {

            double time = doc["time"];
            conditions.timeMs = time;
            for (int i = 0; i < NUM_DIALS; i++)
            {
              Dial dial = DIALS[i];
              conditions.values[i] = doc["conditions"][dial.key];
            }
          }
        }
      }
      else
      {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    }
  }
  else
  {
    Serial.printf("[HTTPS] Unable to connect\n");
  }

  return conditions;
}