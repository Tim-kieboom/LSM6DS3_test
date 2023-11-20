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
    Vector3* accelerometerOffset = new Vector3();
    float detectValue = 0.05;

public:
    Accelerometer(LSM6DS3* IMU);
    Accelerometer(LSM6DS3* IMU, float detectValue);
    ~Accelerometer();

    void getAcceleration(Vector3* accelerations, Vector3* gravityConstant); 
    Vector3* readAccelerometer();
    Vector3* getAverageReading();

    Vector3* calibrateGravityAccelerometer();

    void setDetectValue(float detectValue);

private:   
    Vector3* rawReading();

    void underTheDetectedValue_Vector(Vector3* acceleration);
    void underTheDetectedValue(double &acceleration);
    void convertGForceTo_MetersPerSecond(Vector3* acceleration);

};

#endif