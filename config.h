#ifndef Config_h
#define Config_h

#include <WebServer.h>

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

#endif