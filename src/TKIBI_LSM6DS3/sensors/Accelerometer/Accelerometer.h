#pragma once
#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "../../Vector3/Vector3.h"
#include "Arduino.h"
#include <stdint.h>
#include <LSM6DS3.h>
#include <wire.h>

class Accelerometer
{
private:
    LSM6DS3* IMU;
    double detectValue = 0.5;
    
public:
    Accelerometer(LSM6DS3* IMU);
    Accelerometer(LSM6DS3* IMU, double detectValue);

    void getAcceleration(Vector3* accelerations, Vector3* gravityConstant); 
    Vector3* readAccelerometer();

private:   
    void underTheDetectedValue(float &acceleration);
    void convertGForceTo_MetersPerSecond(Vector3* acceleration);

};

#endif