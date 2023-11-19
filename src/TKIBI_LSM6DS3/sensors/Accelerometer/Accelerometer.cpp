#include "Accelerometer.h"

#define UNDER_DETECT_VALUE(x) 

Accelerometer::Accelerometer(LSM6DS3* IMU)
: IMU(IMU)
{

}

Accelerometer::Accelerometer(LSM6DS3* IMU, double detectValue)
: IMU(IMU), detectValue(detectValue)
{

}

void Accelerometer::getAcceleration(Vector3* acceletarion_gForce, Vector3* gravityConstant) 
{
  Vector3* readData = readAccelerometer();
  acceletarion_gForce->replace(readData);
  delete readData;

  acceletarion_gForce->subtract(gravityConstant);

  convertGForceTo_MetersPerSecond(/*out*/ acceletarion_gForce);
}

Vector3* Accelerometer::readAccelerometer()
{
  auto acceleration = new Vector3();
  float x, y, z;

  x = IMU->readFloatAccelX();
  y = IMU->readFloatAccelY();
  z = IMU->readFloatAccelZ();

  underTheDetectedValue(/*out*/ x);
  underTheDetectedValue(/*out*/ y);
  underTheDetectedValue(/*out*/ z);

  acceleration->set(x, y, z);   

  return acceleration;
}

Vector3* Accelerometer::getAverageReading()
{
  Vector3** accelerations = new Vector3*[5];
  Vector3* average = new Vector3();

  for(int8_t i = 0; i < 5; i++)
  {
    accelerations[i] = this->readAccelerometer();
  }

  Vector3* avarageOffset = average->average(accelerations, 5);
  average->replace(avarageOffset);

  for(int8_t i = 0; i < (int8_t)sizeof(accelerations); i++)
  {
    delete accelerations[i];
  }

  delete[] accelerations;
  return average;
}

void Accelerometer::convertGForceTo_MetersPerSecond(Vector3* acceleration)
{
  const double gravityConstantTo_MetersPerSecond = 9.80665;

  acceleration = acceleration->multiply(gravityConstantTo_MetersPerSecond);
}

void Accelerometer::underTheDetectedValue(float &acceleration)
{
  if(acceleration > -detectValue && acceleration< detectValue)
    acceleration = 0;
}