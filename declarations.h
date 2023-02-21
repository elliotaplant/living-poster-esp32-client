#ifndef Declarations_h
#define Declarations_h

struct Dial
{
  String key;
  double rangeLow;
  double rangeHigh;
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

esp_sleep_wakeup_cause_t wakeup();
void servoSetup();
void pinsSetup();
void eepromSetup();
Credentials readCredentials();
void writeCredentials(Credentials);
void wifiConnectLoop(Credentials);
Conditions requestConditions(const char *);
void moveServos(Conditions);
void resetServos();
void hibernateUntilNextHour(uint64_t serverTimeMs);
void hibernateMs(uint64_t millisToSleep);
void setupAccessPoint();
WebServer *createWebServer(String ssidOptions);

#endif