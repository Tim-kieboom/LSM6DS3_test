#include "Gyroscope.h"

Gyroscope::Gyroscope(LSM6DS3* IMU)
: IMU(IMU)
{
  calibrateGyroscope();
}

Gyroscope::Gyroscope(LSM6DS3* IMU, float detectValue)
: IMU(IMU), detectValue(detectValue)
{
  calibrateGyroscope();
}

Gyroscope::~Gyroscope()
{
  delete gyroOffset;
}

Vector3* Gyroscope::readGyroscope()
{
  Vector3* angularAcceleration = new Vector3();
  float x, y, z;

  x = IMU->readFloatGyroX(); 
  y = IMU->readFloatGyroY(); 
  z = IMU->readFloatGyroZ(); 

  angularAcceleration->set(x, y, z);
  angularAcceleration->subtract(gyroOffset);

  return angularAcceleration;
}

void Gyroscope::setDetectValue(float detectValue)
{
  this->detectValue = detectValue;
}

void Gyroscope::underTheDetectedValue(float &angularAcceleration)
{
  if(angularAcceleration > -detectValue && angularAcceleration< detectValue)
    angularAcceleration = 0;
}

void Gyroscope::calibrateGyroscope()
{
  Vector3** gyroArray = new Vector3*[10];

  for(uint8_t i = 0; i < (uint8_t)sizeof(gyroArray); i++)
  {
    gyroArray[i] = this->readGyroscope();
  }

  Vector3* avarageOffset = gyroOffset->average(gyroArray);
  gyroOffset->replace(avarageOffset);

  for(uint8_t i = 0; i < (uint8_t)sizeof(gyroArray); i++)
  {
    delete gyroArray[i];
  }

  delete[] gyroArray;
}
