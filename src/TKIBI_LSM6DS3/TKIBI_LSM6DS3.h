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
    //libary object for gyroscope and accelerometer
    LSM6DS3* IMU = new LSM6DS3(I2C_MODE, 0x6A);

    Accelerometer* accelerometer;
    Gyroscope* gyroscope;

    //the gravity constant meseared by accelometer
    Vector3* gravityCalibration = new Vector3();
    //the distance moved updates with checkIfDistanceMoved()
    Vector3* distanceMoved = new Vector3();

    //time between readings in milliseconds for accelerometer
    uint16_t accelerometerReadingSpeed_ms = 100;
    //time between readings in milliseconds for gyroscope 
    uint16_t gyroscopeReadingSpeed_ms = 100;

    //keeps time between readings in milliseconds for accelerometer
    WaitTimer accelerometerTimer = WaitTimer();
    //keeps time between readings in milliseconds for gyroscope
    WaitTimer gyroscopeTimer = WaitTimer();

public:
//-------------------------------- CONSTRUCTORS --------------------------------


    TKIBI_LSM6DS3();
    TKIBI_LSM6DS3(uint16_t accelerometerReadingSpeed_ms, uint16_t gyroscopeReadingSpeed_ms);
    ~TKIBI_LSM6DS3();


//-------------------------------- EVENTS --------------------------------


    //needs to be called to start object (starts waitTimers and gets gravityConstance)
    void start();
    
    //resets waitTimers and clears distanceMoved
    void reset();
    void resetAccelerometerTimer();
    void resetGyroscopeTimer();
    //clears distanceMoved
    void resetDistanceMoved();

    //restart IMU, gravityConstance, waitTimers and clears distanceMoved
    void restart();


//-------------------------------- SENSOR_DATA --------------------------------


    //if sensor moved add distance to DistanceMoved
    void checkIfDistanceMoved();


//-------------------------------- printData --------------------------------


    //print data directly from the accelerometer and gyroscope classes
    void printRawData();
    //print data directly from the accelerometer
    void printRawAccelerometerData();
    //print data directly from the gyroscope
    void printRawGyroscopeData();


//-------------------------------- GETTERS --------------------------------


    //get vector3 of the data directly from the accelerometer
    Vector3* getRawAccelerometerData();
    //get vector3 of the data directly from the gyroscope
    Vector3* getRawGyroscopeData();


//-------------------------------- SETTERS --------------------------------


    void setAccelerometerReadingSpeed_ms(uint16_t readingSpeed);
    void setGyroscopeReadingSpeed_ms(uint16_t readingSpeed);

    void setAccelerometerDetectValue(float detectValue);
    void setGyroscopeDetectValue(float detectValue);


//-------------------------------- PRIVATE --------------------------------


private:
    //getDistance() per axis in vector3
    void getDistanceVector3(Vector3* tempDistance);
    //get distance from the acceleration
    double getDistance(double acceleration);

    //starts connection with sensor using i2c communication
    void setup_Sensor();
};

#endif