#pragma once
#ifndef GYROSCOPE_H_
#define GYROSCOPE_H_

#include "../../Vector3/Vector3.h"
#include "Arduino.h"
#include <stdint.h>
#include <LSM6DS3.h>
#include <wire.h>

class Gyroscope
{
private:
    LSM6DS3* IMU;
    Vector3* gyroOffset = new Vector3();
    float detectValue = 0.5;

public:
    Gyroscope(LSM6DS3* IMU);
    Gyroscope(LSM6DS3* IMU, float detectValue);
    ~Gyroscope();

    Vector3* readGyroscope();

    void setDetectValue(float detectValue);
    
private:
    void underTheDetectedValue(float &acceleration);
    void calibrateGyroscope();
};

#endif