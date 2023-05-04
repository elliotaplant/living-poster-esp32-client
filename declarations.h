#ifndef Declarations_h
#define Declarations_h

struct Dial
{
  char key[32];
  double rangeLow;
  double rangeHigh;
  int pin;
};

struct Conditions
{
  uint64_t timeMs;
  bool valid;
  double values[3];
};

struct Credentials
{
  String ssid;
  String password;
};

esp_sleep_wakeup_cause_t wakeup();
void blink();
void setupServos();
void startServos();
void pinsSetup();
void eepromSetup();
Credentials readCredentials();
void writeCredentials(Credentials);
bool connectAndTestWifi(Credentials);
void tryWifiOrSetupAccessPoint(Credentials);
void disconnectWifi();
Conditions requestConditions(String, String, String, String);
void moveServos(Conditions);
void resetServos();
void hibernateUntilNextCycle(uint64_t serverTimeMs);
void hibernateMs(uint64_t millisToSleep);
void setupAccessPoint();
WebServer *createWebServer(String ssidOptions);

#endif