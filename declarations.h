#ifndef Declarations_h
#define Declarations_h

struct Dial
{
  String key;
  int rangeLow;
  int rangeHigh;
  int pin;
};

struct Conditions
{
  uint64_t timeMs;
  double values[3];
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
Conditions requestConditions(const char *);
void moveServos(Conditions);
void hibernate(uint64_t serverTimeMs);
void setupAccessPoint();
WebServer *createWebServer(String ssidOptions);

#endif