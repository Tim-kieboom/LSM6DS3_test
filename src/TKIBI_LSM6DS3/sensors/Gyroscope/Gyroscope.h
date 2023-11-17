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
    double detectValue = 0.5;

public:
    Gyroscope(LSM6DS3* IMU);
    Gyroscope(LSM6DS3* IMU, double detectValue);

    Vector3* readGyroscope();
    
private:
    void underTheDetectedValue(float &acceleration);

};

#endif