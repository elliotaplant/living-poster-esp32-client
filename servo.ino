#include <ESP32Servo.h>

Servo servos[NUM_DIALS]; // create servo object to control a servo

// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
void setupServos()
{
  // Set servo output pin to output
  pinMode(SERVO_CONTROL_PIN, OUTPUT);

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  for (int i = 0; i < NUM_DIALS; i++)
  {
    servos[i].setPeriodHertz(SERVO_PWM_FREQUENCY);
    servos[i].attach(DIALS[i].pin, SERVO_DUTY_CYCLE_LOW, SERVO_DUTY_CYCLE_HIGH);
  }
}

void startServos()
{
  Serial.println("Setting servo control pin HIGH");
  digitalWrite(SERVO_CONTROL_PIN, HIGH); // Start voltage flow to servos through transistor
}

void stopServos()
{
  digitalWrite(SERVO_CONTROL_PIN, LOW); // End voltage flow to servos through transistor
  Serial.println("Setting servo control pin LOW");
}

void moveServos(Conditions conditions)
{
  startServos();
  for (int i = 0; i < NUM_DIALS; i++)
  {
    Dial dial = DIALS[i];
    double value = conditions.values[i];
    double pct = (value - dial.rangeLow) / (dial.rangeHigh - dial.rangeLow);
    double degrees = 180 * (1 - pct); // Negative because the rotation is reversed
    Serial.printf(
        "Moving dial %s with value %f (pct %f) to degrees %f\n",
        dial.key,
        conditions.values[i],
        pct,
        degrees);

    servos[i].write(degrees); // tell servo to go to position in variable 'pos'
    delay(200); // Add gap between movements to lower max current
  }
  delay(200); // Wait for last servo to get to position
  stopServos();
}

void resetServos()
{
  startServos();
  Serial.println("Resetting servos");
  for (int i = 0; i < NUM_DIALS; i++)
  {
    Dial dial = DIALS[i];
    servos[i].write(180);
  }
  delay(400);
  stopServos();
}