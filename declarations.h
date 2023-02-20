#ifndef Declarations_h
#define Declarations_h

struct Dial
{
  String key;
  int rangeLow;
  int rangeHigh;
  int pin;
};

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
void requestConditions(const char *);
void moveServos();
void hibernate();
void setupAccessPoint();
WebServer *createWebServer(String ssidOptions);

#endif