#ifndef Config_h
#define Config_h

// Change the beach and poster_id for each poster
const String DATA_URL = "http://living-poster.elliotplant.com/";
const String BEACH = "sunsetCliffs";
const String POSTER_ID = "1";

// Servo
const int CYCLE_TIME_MS = 60 * 60 * 1000; // 60 mins
const int SERVO_PWM_FREQUENCY = 50;
const int SERVO_DUTY_CYCLE_LOW = 1000;
const int SERVO_DUTY_CYCLE_HIGH = 2000;

// Pins
const int SERVO_CONTROL_PIN = 13;
const int BATTERY_VOLTAGE_PIN = 36;

// Dials
const int NUM_DIALS = 3;
Dial DIALS[NUM_DIALS] = {
    {"surfHeight", 0, 10, 26},
    {"waterTemp", 55, 80, 33},
    {"windSpeed", 0, 20, 32},
};

#endif