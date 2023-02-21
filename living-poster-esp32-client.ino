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

    // TODO: Turn on access point
    hibernateMs(5000);
  }
  else
  {
    // Read WiFi credentials
    Credentials credentials = readCredentials();

    // Connect to wifi or make a server to get wifi credentials
    wifiConnectLoop(credentials);

    // Query conditions
    Conditions conditions = requestConditions(DATA_URL);

    // Interpret conditions to dial angle
    // Change the dial angles
    moveServos(conditions);

    // Hibernate that many ms
    hibernateUntilNextHour(conditions.timeMs);
  }
}
