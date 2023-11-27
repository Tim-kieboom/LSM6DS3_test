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
    //libary object for accelerometer
    LSM6DS3* IMU;
    Vector3* accelerometerOffset = new Vector3();

    float detectValue = 0.04;
    
public:

//-------------------------------- CONTRUCTORS --------------------------------


    Accelerometer(LSM6DS3* IMU);
    Accelerometer(LSM6DS3* IMU, float detectValue);
    ~Accelerometer();


//-------------------------------- SERNOR_DATA --------------------------------


    void getAcceleration(Vector3* accelerations, Vector3* gravityConstant); 

    //rawReading minus the accelerometerOffset and using the underTheDetectedValue_Vector() function
    Vector3* readAccelerometer();

    //getting the avarage of 10 accelerometer readings
    Vector3* getAverageReading();

    Vector3* calibrateGravityAccelerometer();

    Vector3* rawReading();


//-------------------------------- SETTERS --------------------------------


    void setDetectValue(float detectValue);


//-------------------------------- PRIVATES --------------------------------


private:
    void underTheDetectedValue_Vector(Vector3* acceleration);
    void underTheDetectedValue(double &acceleration);
    void convertGForceTo_MetersPerSecond(Vector3* acceleration);

};

#endif