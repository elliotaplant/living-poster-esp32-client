#ifndef Declarations_h
#define Declarations_h

struct Credentials
{
  String ssid;
  String password;
};

void pinsSetup();
void eepromSetup();
Credentials readCredentials();
void writeCredentials(Credentials);
void wifiConnectLoop(Credentials);
String requestURL(const char *);
void moveServos();
void hibernate();
void setupAccessPoint();
WebServer *createWebServer(String ssidOptions);

#endif