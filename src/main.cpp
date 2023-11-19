#include "TKIBI_LSM6DS3/TKIBI_LSM6DS3.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting");

  TKIBI_LSM6DS3* sensor = new TKIBI_LSM6DS3(500, 500);
  sensor->start();

  Gyroscope gyro = Gyroscope(new LSM6DS3(I2C_MODE, 0x6A));

  while(1)
  {
    sensor->checkIfDistanceMoved();
    delay(500);
  }

  sensor->reset();
  delete sensor;
}

void loop(){}