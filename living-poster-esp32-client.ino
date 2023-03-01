#include <WebServer.h> // not sure why this has to be here
#include "declarations.h"
#include "constants.h"
#include "config.h"

void setup()
{
  // Setup baud rate, pins
  Serial.begin(115200); // Initialize Serial monitor with baud rate
  eepromSetup();
  pinsSetup();
  servoSetup();
}

// No looping here, just a single pass through
void loop()
{
  // Eventually, handle wifi config with this method
  esp_sleep_wakeup_cause_t wakeupCause = wakeup();
  if (wakeupCause == ESP_SLEEP_WAKEUP_UNDEFINED)
  {
    // Woke up not from sleep, resetting servos
    resetServos();

    // Try to connect to WiFi. If it fails, setup an access point to read credentials
    Credentials credentials = readCredentials();
    tryWifiOrSetupAccessPoint(credentials);

    // After successful WiFI or credential read, hibernate
    hibernateMs(5000);
  }
  else
  {
    // Read WiFi credentials
    Credentials credentials = readCredentials();

    // Connect to wifi or make a server to get wifi credentials
    bool connectSuccess = connectAndTestWifi(credentials);

    if (connectSuccess)
    {

      // Query conditions
      Conditions conditions = requestConditions(DATA_URL, BEACH, POSTER_ID, millis());

      // TODO: Check to see if conditions match previous conditions and don't move the servos

      // Change the dial angles and interpret conditions to dial angle
      moveServos(conditions);

      // Blink to show success
      blink();

      // Hibernate that many ms
      hibernateUntilNextCycle(conditions.timeMs);
    }
    else
    {
      // Query failed, sleep for 1hr
      hibernateMs(60 * 60 * 1000);
    }
  }
}
