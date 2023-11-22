#include "TKIBI_LSM6DS3/TKIBI_LSM6DS3.h"

void setup_serial()
{
  Serial.begin(115200);
  Serial.println("Starting");
}

void setup()
{
  setup_serial();

  TKIBI_LSM6DS3* sensor = new TKIBI_LSM6DS3(500, 500);
  sensor->start();

  while(1)
  {
    sensor->printRawData();
    delay(500);
  }
}

void loop(){}