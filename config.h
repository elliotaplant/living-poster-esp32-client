#ifndef Config_h
#define Config_h

// Change the beach and poster_id for each poster
const String DATA_URL = "https://living-poster.elliotaplant9602.workers.dev";
const String BEACH = "blacks";
const String POSTER_ID = "1";

// Servo
const int CYCLE_TIME_MS = 2 * 60 * 1000; // 2 mins
const int SERVO_PWM_FREQUENCY = 50;
const int SERVO_DUTY_CYCLE_LOW = 600;
const int SERVO_DUTY_CYCLE_HIGH = 2500;

// Pins
const int SERVO_CONTROL_PIN = 21;
const int BATTERY_VOLTAGE_PIN = 2;

// Dials
const int NUM_DIALS = 3;
Dial DIALS[NUM_DIALS] = {
    {"surfHeight", 0, 10, 13},
    {"waterTemp", 55, 80, 12},
    {"windSpeed", 0, 20, 14},
};

#endif