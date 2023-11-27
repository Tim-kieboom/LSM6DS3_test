#include "Gyroscope.h"

//-------------------------------- CONSTRUCTOR --------------------------------

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

//-------------------------------- SENSOR_DATA --------------------------------

void Gyroscope::getAngularAcceleration(Vector3* angularAcceleration)
{
  Vector3* readData = readGyroscope();

  //--add filters--

  angularAcceleration->replace(readData);
}


Vector3* Gyroscope::readGyroscope()
{
  Vector3* angularAcceleration = rawReading();

  angularAcceleration->subtract(gyroOffset);
  underTheDetectedValue_Vector(/*out*/ angularAcceleration);

  return angularAcceleration;
}

Vector3* Gyroscope::getAverageReading()
{
  Vector3** gyroArray = new Vector3*[10];

  for(uint8_t i = 0; i < (uint8_t)sizeof(gyroArray); i++)
  {
    gyroArray[i] = this->readGyroscope();
  }

  Vector3* avarageOffset = gyroOffset->average(gyroArray, (uint16_t)sizeof(gyroArray));

  for(uint8_t i = 0; i < (uint8_t)sizeof(gyroArray); i++)
  {
    delete gyroArray[i];
  }

  delete[] gyroArray;
  return avarageOffset;
}

Vector3* Gyroscope::rawReading()
{
  Vector3* angularAcceleration = new Vector3();
  float x, y, z;

  x = IMU->readFloatGyroX(); 
  y = IMU->readFloatGyroY(); 
  z = IMU->readFloatGyroZ(); 

  angularAcceleration->set(x, y, z);

  return angularAcceleration;
}

//-------------------------------- SETTERS --------------------------------

void Gyroscope::setDetectValue(float detectValue)
{
  this->detectValue = detectValue;
}

//-------------------------------- PRIVATES --------------------------------

void Gyroscope::underTheDetectedValue_Vector(Vector3* angularAcceleration)
{
  double x = angularAcceleration->getX();
  double y = angularAcceleration->getY();
  double z = angularAcceleration->getZ();

  underTheDetectedValue(/*out*/ x);
  underTheDetectedValue(/*out*/ y);
  underTheDetectedValue(/*out*/ z);

  angularAcceleration->set(x, y, z);
}

void Gyroscope::underTheDetectedValue(double &angularAcceleration)
{
  if(angularAcceleration > -detectValue && angularAcceleration< detectValue)
    angularAcceleration = 0;
}

void Gyroscope::calibrateGyroscope()
{
  Vector3* avarageOffset = getAverageReading();
  gyroOffset->replace(avarageOffset);
}
