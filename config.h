#ifndef Config_h
#define Config_h

// Change the beach and poster_id for each poster
const String DATA_URL = "http://living-poster.elliotplant.com/";
const String BEACH = "montara";
const String POSTER_ID = "3";

// Servo
const int CYCLE_TIME_MS = 60 * 60 * 1000; // 60 mins
const int SERVO_PWM_FREQUENCY = 50;
const int SERVO_DUTY_CYCLE_LOW = 600;
const int SERVO_DUTY_CYCLE_HIGH = 2500;

// Pins
const int SERVO_CONTROL_PIN = 13;
const int BATTERY_VOLTAGE_PIN = 36;

// Dials
const int NUM_DIALS = 3;
Dial DIALS[NUM_DIALS] = {
    {"surfHeight", 0, 15, 26},
    {"waterTemp", 40, 65, 33},
    {"windSpeed", 0, 40, 32},
};

// Server
const IPAddress SERVER_IP = new IPAddress(10, 0, 0, 1);

#endif