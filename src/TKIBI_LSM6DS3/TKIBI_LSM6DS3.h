#pragma once
#ifndef TKIBI_LSM6DS3_H
#define TKIBI_LSM6DS3_H

#include "Arduino.h"
#include "sensors/Accelerometer/Accelerometer.h"
#include "sensors/Gyroscope/Gyroscope.h"
#include "Vector3/Vector3.h"
#include "timer/WaitTimer.h"

class TKIBI_LSM6DS3
{
private:
    LSM6DS3* IMU = new LSM6DS3(I2C_MODE, 0x6A);

    uint16_t accelerometerReadingSpeed_ms = 100;
    uint16_t gyroscopeReadingSpeed_ms = 100;

    Vector3* gravityCalibration = new Vector3();
    Vector3* distanceMoved = new Vector3();

    Accelerometer* accelerometer;
    Gyroscope* gyroscope;

    WaitTimer timer = WaitTimer();

public:
    TKIBI_LSM6DS3();
    TKIBI_LSM6DS3(uint16_t accelerometerReadingSpeed_ms, uint16_t gyroscopeReadingSpeed_ms);
    ~TKIBI_LSM6DS3();


    void start();
    void reset();

    void checkIfDistanceMoved();
    void printRawData();

    Vector3* getRawAccelerometerData();
    Vector3* getRawGyroscopeData();

private:
    void getDistanceVector3(Vector3* tempDistance);
    double getDistance(double acceleration);
    void setup_Sensor();
};

#endif