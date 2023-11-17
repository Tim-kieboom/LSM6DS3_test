#include "Gyroscope.h"

Gyroscope::Gyroscope(LSM6DS3* IMU)
: IMU(IMU)
{

}

Gyroscope::Gyroscope(LSM6DS3* IMU, double detectValue)
: IMU(IMU), detectValue(detectValue)
{

}

Vector3* Gyroscope::readGyroscope()
{
    Vector3* angularAcceleration = new Vector3();
    float x, y, z;

    x = IMU->readFloatGyroX(); 
    y = IMU->readFloatGyroY(); 
    z = IMU->readFloatGyroZ(); 

    angularAcceleration->set(x, y, z);

    return angularAcceleration;
}

void Gyroscope::underTheDetectedValue(float &angularAcceleration)
{
  if(angularAcceleration > -detectValue && angularAcceleration< detectValue)
    angularAcceleration = 0;
}
