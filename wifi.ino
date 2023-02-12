#include <WiFi.h>
#include <EEPROM.h>

// Establishing Local server at port 80
Credentials credentials;
int NUM_WIFI_ACCESS_POINT_ATTEMPTS = 10;

// Gets credentials from disk, if they exist
void wifiSetup()
{
    Serial.println("Reading EEPROM ssid");
    credentials = readCredentials();
}

// Uses credentials to connect to WiFi or creates a server to get those credentials
void wifiConnectLoop()
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
    Wifi.begin(credentials.ssid.c_str(), credentials.password.c_str());
}

bool testWifi()
{
    Serial.print("Testing WiFi connection ");
    for (int i = 0; i < 20; i++)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("WiFi connection successful");
            return true;
        }
        delay(500);
        Serial.print("*");
    }
    Serial.println("Failed to connect to WiFi");
    return false;
}
