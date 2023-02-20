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
  // // Read WiFi credentials
  // Credentials credentials = readCredentials();

  // // Connect to wifi or make a server to get wifi credentials
  // wifiConnectLoop(credentials);

  // // Query conditions
  // Conditions conditions = requestConditions(DATA_URL);

  for (int deg = 0; deg < 180; deg += 10)
  {
    writeServoPosition(deg);
  }

  for (int deg = 180; deg > 0; deg -= 10)
  {
    writeServoPosition(deg);
  }

  //     // Interpret conditions to dial angle
  //     // Change the dial angles
  //     moveServos(conditions);

  // // Find the number of ms until next switch (maybe get time from response?)
  // // Hibernate that many ms
  // hibernate(conditions.timeMs);
}
