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

    //object where the accelerometer readings happen
    Accelerometer* accelerometer;
    //the measurement of the accelerometer
    Vector3* accelerations = new Vector3();
    //the speed before the acceleroration
    double initialSpeed = 0;

    //object where the gyroscope readings happen
    Gyroscope* gyroscope;
    //the measurement of the gyroscope
    Vector3* gyroAccelerations = new Vector3();


    //the gravity constant meseared by accelometer
    Vector3* gravityCalibration = new Vector3();
    //the distance moved, updates with checkIfDistanceMoved()
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
    TKIBI_LSM6DS3(double initialSpeed);
    TKIBI_LSM6DS3(uint16_t accelerometerReadingSpeed_ms, uint16_t gyroscopeReadingSpeed_ms);
    TKIBI_LSM6DS3(uint16_t accelerometerReadingSpeed_ms, uint16_t gyroscopeReadingSpeed_ms, double initialSpeed);
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


    //print data directly from the accelerometer and gyroscope 
    void printRawData();
    //print data directly from the accelerometer
    void printRawAccelerometerData();
    //print data directly from the gyroscope
    void printRawGyroscopeData();

    //print data from the accelerometer and gyroscope with methode readAccelerometer() and readGyroscope()
    void printData();
    //print data from the accelerometer with methode readAccelerometer()
    void printAccelerometerData();
    //print data from the gyroscope with methode readGyroscope()
    void printGyroscopeData();


//-------------------------------- GETTERS --------------------------------


    //get vector3 of the data directly from the accelerometer
    Vector3* getRawAccelerometerData();
    //get vector3 of the data directly from the gyroscope
    Vector3* getRawGyroscopeData();

    //get the accelermeter Object
    Accelerometer* getAccelerometer();
    //get the gyroscope Object
    Gyroscope* getGyroscope();

    //get the initialSpeed variable
    double getCurrentSpeed();


//-------------------------------- SETTERS --------------------------------


    void setAccelerometerReadingSpeed_ms(uint16_t readingSpeed);
    void setGyroscopeReadingSpeed_ms(uint16_t readingSpeed);

    void setAccelerometerDetectValue(float detectValue);
    void setGyroscopeDetectValue(float detectValue);

    //set the initialSpeed variable
    void setCurrentSpeed(double initialSpeed);


//-------------------------------- PRIVATE --------------------------------


private:
    //getDistance() per axis in vector3
    void getDistanceVector3(Vector3* tempDistance, uint64_t beginReadingTime);
    //get distance from the acceleration
    double getDistance(double acceleration, uint64_t sensorReadingTime);

    //starts connection with sensor using i2c communication
    void setup_Sensor();
};

#endif