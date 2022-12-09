#include "MPU.h"

MPU::MPU() : mpu(Wire) {}

void MPU::setup()
{
    Wire.begin();

    byte status = mpu.begin();
    Serial.println(status);
    if (status != 0)
    {
        Serial.printf("Could not find MPU6050; Status: %d\n", status);
        return;
    }
    else
    {
        initialized = true;
        Serial.println("Connected to MPU6050");
    }

    Serial.print(F("Calculating offsets, do not move MPU6050..."));
    mpu.calcOffsets();
    Serial.println("...Done!");
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