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
    //libary object for gyroscope
    LSM6DS3* IMU;

    //the offset inaccuratie of the gyroscope (for example [x:1, y:2, z:1] at an expected value of [x:0, y:0, z:0] or no rotation)
    Vector3* gyroOffset = new Vector3();
    float detectValue = 0.5;

public:
//-------------------------------- CONSTRUCTOR --------------------------------


    Gyroscope(LSM6DS3* IMU);
    Gyroscope(LSM6DS3* IMU, float detectValue);
    ~Gyroscope();


//-------------------------------- SENSOR_DATA --------------------------------


    //rawReading minus the gyroOffset and using the underTheDetectedValue_Vector() function
    Vector3* readGyroscope();

    //getting the avarage of 10 gyroscope readings
    Vector3* getAverageReading();

    //the raw reading of the gyroscope
    Vector3* rawReading();


//-------------------------------- SETTERS --------------------------------


    //value used in underTheDectedValue() function
    void setDetectValue(float detectValue);


//-------------------------------- PRIVATES --------------------------------


private:
    //underTheDetectedValue per axis in vector3
    void underTheDetectedValue_Vector(Vector3* angularAcceleration);
    //function that if value is under detectValue than make value 0
    void underTheDetectedValue(double &angularAcceleration);

    //calbrate gyroscopeOffset by getAvarageReading() at rotation of 0
    void calibrateGyroscope();
};

#endif