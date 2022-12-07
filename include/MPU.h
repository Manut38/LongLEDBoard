#include <Wire.h>
#include <MPU6050_light.h>

#define ACCEL_DEBOUNCE_TIME 200
class MPU
{
private:
    MPU6050 mpu;
    bool initialized;

    // Debounce
    unsigned long accelDebounceTimer;

    // Functions
    void processAccel();
    void processTilt();

public:
    MPU();
    void setup();
    void loop();
    bool wasAccelerated;
    int tiltAngle;
};