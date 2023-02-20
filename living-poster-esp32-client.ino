#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>

String BEACH = "blacks";

WebServer server(80); // I can probably move this to access-point or server
const int BUTTON_PIN = 15;
const int LED_PIN = 5;

// Establishing Local server at port 80
int NUM_WIFI_ACCESS_POINT_ATTEMPTS = 10;
int EEPROM_SSID_SPACE = 32;
const char *DATA_URL = "https://living-poster.elliotaplant9602.workers.dev";

struct Credentials
{
  String ssid;
  String password;
};

void setup()
{
  // Setup baud rate, pins
  Serial.begin(115200); // Initialize Serial monitor with baud rate
  EEPROM.begin(512);    // Initializing EEPROM with 512 bytes (can we move to EEPROM.ino?)
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // LED off
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
