#include <WiFi.h>

// Uses credentials to connect to WiFi or creates a server to get those credentials
void wifiConnectLoop(Credentials credentials)
{
  for (int i = 0; i < NUM_WIFI_ACCESS_POINT_ATTEMPTS; i++)
  {
    // Attempt to connect to wifi
    connectWifi(credentials);

    // If successful, exit
    if (testWifi())
      return;

    // If unsuccessful, create the configuration server
    setupAccessPoint();
  }
}

void connectWifi(Credentials credentials)
{
  WiFi.begin(credentials.ssid.c_str(), credentials.password.c_str());
}

bool testWifi()
{
  Serial.print("Testing WiFi connection ");
  for (int i = 0; i < 30; i++)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("WiFi connection successful");
      return true;
    }
    delay(1000);
    Serial.print("*");
  }
  Serial.println();
  Serial.println("Failed to connect to WiFi");
  return false;
}
