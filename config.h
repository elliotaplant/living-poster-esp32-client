#ifndef Config_h
#define Config_h

// Change this for each poster
const char *DATA_URL = "https://living-poster.elliotaplant9602.workers.dev/?beach=blacks";

const int SERVO_PWM_FREQUENCY = 50;
const int SERVO_DUTY_CYCLE_LOW = 600;
const int SERVO_DUTY_CYCLE_HIGH = 2500;
const int NUM_DIALS = 3;
Dial DIALS[NUM_DIALS] = {
    {"surfHeight", 0, 10, 13},
    {"waterTemp", 55, 80, 14},
    {"windSpeed", 0, 20, 15},
};

#endif