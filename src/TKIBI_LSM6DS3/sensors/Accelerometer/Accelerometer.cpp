#include "Accelerometer.h"


//---------------- CONTRUCTORS ----------------

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
  delete accelerometerOffset;
}

//---------------- READINGS ----------------


void Accelerometer::getAcceleration(Vector3* acceletarion_gForce, Vector3* gravityConstant) 
{
  Vector3* readData = readAccelerometer();
  acceletarion_gForce->replace(readData);
  delete readData;

  //acceletarion_gForce->subtract(gravityConstant);

  convertGForceTo_MetersPerSecond(/*out*/ acceletarion_gForce);
}

Vector3* Accelerometer::readAccelerometer()
{
  Vector3* acceleration = rawReading();

  //underTheDetectedValue_Vector(/*out*/ acceleration);
  acceleration->subtract(accelerometerOffset);

  return acceleration;
}

Vector3* Accelerometer::getAverageReading()
{
  Vector3** accelerations = new Vector3*[10];
  Vector3* average = new Vector3();

  for(uint8_t i = 0; i < (uint8_t)sizeof(accelerations); i++)
  {
    accelerations[i] = rawReading();
  }

  Vector3* avarageOffset = average->average(accelerations);
  average->replace(avarageOffset);

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

  accelerometerOffset->replace(averageReading->subtract(expectedReading));
  accelerometerOffset->print();

  delete expectedReading;
  return averageReading;
}

void Accelerometer::setDetectValue(float detectValue)
{
  this->detectValue = detectValue;
}


//---------------- PRIVATES ----------------

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
  if(acceleration < -detectValue && acceleration > detectValue)
    acceleration = 0;
}