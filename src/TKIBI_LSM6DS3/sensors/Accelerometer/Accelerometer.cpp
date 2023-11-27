#include "Accelerometer.h"
#define SUBTRACT_ACCELEROMETER_OFFSET(vectorPointer) vectorPointer = vectorPointer->subtract(accelerometerOffset);


//-------------------------------- CONTRUCTORS --------------------------------


Accelerometer::Accelerometer(LSM6DS3* IMU)
: IMU(IMU)
{

}

Accelerometer::Accelerometer(LSM6DS3* IMU, float detectValue)
: IMU(IMU), detectValue(detectValue)
{

}

Accelerometer::~Accelerometer()
{

}


//-------------------------------- SERNOR_DATA --------------------------------


void Accelerometer::getAcceleration(Vector3* acceletarion_gForce, Vector3* gravityConstant) 
{
  Vector3* readData = getAverageReading();
  acceletarion_gForce->replace(readData);

  acceletarion_gForce->subtract(gravityConstant);

  convertGForceTo_MetersPerSecond(/*out*/ acceletarion_gForce);
  underTheDetectedValue_Vector(/*out*/ acceletarion_gForce);
}

Vector3* Accelerometer::readAccelerometer()
{
  Vector3* acceleration = rawReading();
  
  SUBTRACT_ACCELEROMETER_OFFSET(acceleration);
  underTheDetectedValue_Vector(/*out*/ acceleration);

  return acceleration;
}

Vector3* Accelerometer::getAverageReading()
{
  Vector3** accelerations = new Vector3*[100];
  Vector3* average = new Vector3();

  for(uint8_t i = 0; i < (uint8_t)sizeof(accelerations); i++)
  {
    accelerations[i] = rawReading();
  }

  Vector3* tempAverage = average->average(accelerations, (uint16_t)sizeof(accelerations));
  SUBTRACT_ACCELEROMETER_OFFSET(tempAverage);
  average->replace(tempAverage);

  for(uint8_t i = 0; i < (uint8_t)sizeof(accelerations); i++)
  {
    delete accelerations[i];
  }

  delete[] accelerations;
  return average;
}

Vector3* Accelerometer::calibrateGravityAccelerometer()
{
  Vector3* averageReading = getAverageReading();
  Vector3* expectedReading = new Vector3(0,0,1);

  Vector3* offsetOfExpectedReading = averageReading->copyPointer();
  offsetOfExpectedReading = offsetOfExpectedReading->subtract(expectedReading);

  accelerometerOffset->replace(offsetOfExpectedReading);
  accelerometerOffset->print();


  delete expectedReading;
  SUBTRACT_ACCELEROMETER_OFFSET(averageReading);
  return averageReading;
}

Vector3* Accelerometer::rawReading()
{
  auto acceleration = new Vector3();
  float x, y, z;

  x = IMU->readFloatAccelX();
  y = IMU->readFloatAccelY();
  z = IMU->readFloatAccelZ();

  acceleration->set(x, y, z); 
  return acceleration;  
}


//-------------------------------- SETTERS --------------------------------


void Accelerometer::setDetectValue(float detectValue)
{
  this->detectValue = detectValue;
}


//-------------------------------- PRIVATES --------------------------------


void Accelerometer::convertGForceTo_MetersPerSecond(Vector3* acceleration)
{
  const double gravityConstantTo_MetersPerSecond = 9.80665;

  acceleration = acceleration->multiply(gravityConstantTo_MetersPerSecond);
}

void Accelerometer::underTheDetectedValue_Vector(Vector3* acceleration)
{
  double x = acceleration->getX();
  double y = acceleration->getY();
  double z = acceleration->getZ();

  underTheDetectedValue(/*out*/ x);
  underTheDetectedValue(/*out*/ y);
  underTheDetectedValue(/*out*/ z);

  acceleration->set(x, y, z);
}

void Accelerometer::underTheDetectedValue(double &acceleration)
{
  if(acceleration > (double)0.04 * -1 && acceleration < (double)0.04)
    acceleration = 0;
}