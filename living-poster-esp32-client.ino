#include <WebServer.h> // not sure why this has to be here
#include "declarations.h"

String BEACH = "blacks";

const int BUTTON_PIN = 15;
const int LED_PIN = 5;

const int EEPROM_SSID_SPACE = 32;
const int NUM_WIFI_ACCESS_POINT_ATTEMPTS = 10;
const char *DATA_URL = "https://living-poster.elliotaplant9602.workers.dev";

void setup()
{
  // Setup baud rate, pins
  Serial.begin(115200); // Initialize Serial monitor with baud rate
  eepromSetup();
  pinsSetup();
}

// No looping here, just a single pass through
void loop()
{
  // Read WiFi credentials
  Credentials credentials = readCredentials();

  // Connect to wifi or make a server to get wifi credentials
  wifiConnectLoop(credentials);

  // Query conditions
  String conditionsResponseJson = requestURL(DATA_URL);

  // Parse conditions
  // parseResponse(conditionsResponseJson);

  // Interpret conditions to dial angle
  // Change the dial angles
  moveServos();

  // Find the number of ms until next switch (maybe get time from response?)
  // Hibernate that many ms
  hibernate();
}
