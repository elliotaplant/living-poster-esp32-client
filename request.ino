#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Request -------------------------------------------------
String requestURL(const char *url)
{
  String response = "";

  Serial.println("Connecting to domain: " + String(url));

  // Use WiFiClient class to create TCP connections
  WiFiClientSecure *client = new WiFiClientSecure;
  if (client)
  {
    // Not using an SSL cert because there's no secret info
    client->setInsecure();

    // Create an HTTPClient instance
    HTTPClient https;

    // Initializing an HTTPS communication using the secure client
    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, url))
    {
      Serial.print("[HTTPS] GET...\n");
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
            return "";
          }

          double surfHeight = doc[BEACH]["surfHeight"];
          double windSpeed = doc[BEACH]["windSpeed"];
          double waterTemp = doc[BEACH]["waterTemp"];
          Serial.printf("surfHeight: %f | windSpeed: %f | waterTemp: %f\n",
                        waterTemp, windSpeed, surfHeight);
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

  return response;
}