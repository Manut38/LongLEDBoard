#include "MPU.h"

MPU::MPU() : mpu(Wire) {}

void MPU::setup()
{
    Wire.begin();

    byte status = mpu.begin();
    Serial.print(F("MPU6050 status: "));
    Serial.println(status);
    if (status != 0)
    {
        Serial.println("Could not find MPU6050");
        return;
    }
    else
    {
        initialized = true;
        Serial.println("Connected to MPU6050");
    }

    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(200);
    mpu.calcOffsets(); // gyro and accelero
    Serial.println("Done!\n");
}

void MPU::loop()
{
    if (initialized)
    {
        mpu.update();

        processAccel();
        processTilt();
    }
}

void MPU::processAccel()
{
    if (mpu.getAccX() <= -0.8 && wasAccelerated == false && (millis() - accelDebounceTimer >= ACCEL_DEBOUNCE_TIME))
    {
        wasAccelerated = true;
        accelDebounceTimer = millis();
    }
    else
    {
        wasAccelerated = false;
    }
}

void MPU::processTilt()
{
    tiltAngle = mpu.getAngleX();
}