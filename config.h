#ifndef Config_h
#define Config_h

// Change the beach and poster_id for each poster
const String DATA_URL = "http://living-poster.elliotplant.com/";
const String BEACH = "chesapeake";
const String POSTER_ID = "7";

// Servo
const int CYCLE_TIME_MS = 60 * 60 * 1000; // 60 mins
const int SERVO_PWM_FREQUENCY = 50;
const int SERVO_DUTY_CYCLE_LOW = 700;
const int SERVO_DUTY_CYCLE_HIGH = 2500;

// Pins
const int SERVO_CONTROL_PIN = 13;
const int BATTERY_VOLTAGE_PIN = 36;

// Dials
const int NUM_DIALS = 3;
Dial DIALS[NUM_DIALS] = {
    // {"surfHeight", 0, 10, 26},
    {"tide", -4, 4, 26},
    {"waterTemp", 45, 80, 33},
    {"windSpeed", 0, 20, 32},
};

#endif