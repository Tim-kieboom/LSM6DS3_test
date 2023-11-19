#include "TKIBI_LSM6DS3/TKIBI_LSM6DS3.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting");

  TKIBI_LSM6DS3* sensor = new TKIBI_LSM6DS3(500, 500);
  sensor->start();

  while(1)
  {
    sensor->checkIfDistanceMoved();
  }

  sensor->reset();
  delete sensor;
}

void loop(){}