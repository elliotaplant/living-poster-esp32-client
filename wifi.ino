#include <WiFi.h>

// Uses credentials to connect to WiFi or creates a server to get those credentials
bool connectAndTestWifi(Credentials credentials)
{
  // Attempt to connect to wifi
  connectWifi(credentials);

  // If successful, exit
  return testWifi();
}

// Uses credentials to connect to WiFi or creates a server to get those credentials
void tryWifiOrSetupAccessPoint(Credentials credentials)
{
  // Attempt to connect to wifi
  connectWifi(credentials);

  // If successful, exit
  if (!testWifi())
  {

    // If unsuccessful, create the configuration server
    setupAccessPoint();
  }
}

void connectWifi(Credentials credentials)
{
  WiFi.begin(credentials.ssid.c_str(), credentials.password.c_str());
}

void disconnectWifi()
{
  WiFi.disconnect(true);
}

bool testWifi()
{
  Serial.println("Testing WiFi connection");
  for (int i = 0; i < 20; i++)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println();
      Serial.println("WiFi connection successful");
      return true;
    }
    delay(500);
    Serial.print("*");
  }
  Serial.println();
  Serial.println("Failed to connect to WiFi");
  return false;
}
