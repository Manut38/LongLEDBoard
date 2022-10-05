// using namespace std;
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class MPU
{
private:
    Adafruit_MPU6050 mpu;

public:
    void setup();

    void loop();
};