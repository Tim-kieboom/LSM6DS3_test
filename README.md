# TKIBI_LSM6DS3_test
this is a libary made for the measering of distances moved with the use of a LSM6DS3 sensor (an accelerometer and gyroscope) inside of a car.

# libarys used

- arduino.h
- seeed Arduino LSM6DS3/LSM6DS3.h

i used the platformIO extension on VScode to upload the test to a arduino uno 

# TKIBI_LSM6DS3 Object
- Contructors:
```
TKIBI_LSM6DS3::TKIBI_LSM6DS3()
{
  setup_Sensor();
  accelerometer = new Accelerometer(IMU);
  gyroscope = new Gyroscope(IMU);
}

TKIBI_LSM6DS3::TKIBI_LSM6DS3(uint16_t accelerometerReadingSpeed_ms, uint16_t gyroscopeReadingSpeed_ms)
: accelerometerReadingSpeed_ms(accelerometerReadingSpeed_ms), gyroscopeReadingSpeed_ms(gyroscopeReadingSpeed_ms)
{
  setup_Sensor();
  accelerometer = new Accelerometer(IMU);
  gyroscope = new Gyroscope(IMU);
}

TKIBI_LSM6DS3::~TKIBI_LSM6DS3()
{
  delete gravityCalibration;
  delete accelerometer;
  delete gyroscope;
  delete IMU; 
}
```
	- events
	- shared IMU
	- setup IMU
	- gyro/acclr detectvalue, sensorreadingspeed

# Acceleration Object
	- contr
	- acclr offset / gravityConstant
	- averageReading and its affects

# Gyroscope Object
	- contr
	- gyro affset
	- avg reading
