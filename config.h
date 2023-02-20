#ifndef Config_h
#define Config_h

// Change this for each poster
const char *DATA_URL = "https://living-poster.elliotaplant9602.workers.dev/?beach=blacks";

int SERVO_PWN_FREQUENCY = 50;
float SERVO_DUTY_CYCLE_LOW = 2.5;
float SERVO_DUTY_CYCLE_HIGH = 12.5;
Dial DIALS[3] = {
    {"surfHeight", 0, 10, 1},
    {"waterTemp", 55, 80, 2},
    {"windSpeed", 0, 20, 3},
};

#endif