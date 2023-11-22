#include "TKIBI_LSM6DS3.h"
#define GYRO_TIMER gyroscopeTimer.wait_ms(gyroscopeReadingSpeed_ms)
#define ACCELEROMETER_TIMER accelerometerTimer.wait_ms(accelerometerReadingSpeed_ms)

//-------------------------------- CONSTRUCTORS --------------------------------

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

//-------------------------------- EVENTS --------------------------------

void TKIBI_LSM6DS3::start()
{
  gravityCalibration->replace(accelerometer->calibrateGravityAccelerometer());
  accelerometerTimer.startTimer();
  gyroscopeTimer.startTimer();
}

void TKIBI_LSM6DS3::reset()
{
  accelerometerTimer.startTimer();
  gyroscopeTimer.startTimer();
  distanceMoved->replace(new Vector3());
}

void TKIBI_LSM6DS3::resetAccelerometerTimer()
{
  accelerometerTimer.startTimer();
}

void TKIBI_LSM6DS3::resetGyroscopeTimer()
{
  gyroscopeTimer.startTimer();
}

void TKIBI_LSM6DS3::resetDistanceMoved()
{
  distanceMoved->replace(new Vector3());
}

void TKIBI_LSM6DS3::restart()
{
  delete IMU;
  IMU = new LSM6DS3(I2C_MODE, 0x6A);
  setup_Sensor();

  accelerometerTimer.startTimer();
  gyroscopeTimer.startTimer();
  gravityCalibration->replace(accelerometer->calibrateGravityAccelerometer());

  distanceMoved->replace(new Vector3());
}

//-------------------------------- SENSOR_DATA --------------------------------

void TKIBI_LSM6DS3::checkIfDistanceMoved()
{
  static Vector3* gyro;
  static Vector3* accelerations;

  if(GYRO_TIMER)
  {
    delete gyro;
    gyro = gyroscope->readGyroscope();
    gyro->print();
  }

  if(ACCELEROMETER_TIMER)
  {
    delete accelerations;
    accelerations = new Vector3();
    accelerometer->getAcceleration(/*out*/ accelerations, gravityCalibration);
    accelerations->print();
    
    getDistanceVector3(/*out*/ accelerations);

    Vector3* tempDist = distanceMoved->add(accelerations);
    distanceMoved->replace(tempDist);

    Serial.print("distance: ");
    distanceMoved->print();
    Serial.println("");

    delete tempDist;
  }

  accelerometerTimer.updateNow();
  gyroscopeTimer.updateNow();
}

//-------------------------------- PRINT_DATA --------------------------------

void TKIBI_LSM6DS3::printRawData()
{
  printRawAccelerometerData();
  printRawGyroscopeData();
}

void TKIBI_LSM6DS3::printRawAccelerometerData()
{
  Vector3* rawAcclrData = accelerometer->readAccelerometer();

  Serial.println("Accelerometer raw data:");
  rawAcclrData->print();
  Serial.println();

  delete rawAcclrData;
}
void TKIBI_LSM6DS3::printRawGyroscopeData()
{
  Vector3* rawGyroData = gyroscope->readGyroscope();

  Serial.println("Gyroscop raw data:");
  rawGyroData->print();
  Serial.println();

  delete rawGyroData;
}

//-------------------------------- GETTERS --------------------------------

Vector3* TKIBI_LSM6DS3::getRawAccelerometerData()
{
  return accelerometer->readAccelerometer(); 
}

Vector3* TKIBI_LSM6DS3::getRawGyroscopeData()
{
  return gyroscope->readGyroscope();
}

//-------------------------------- SETTERS --------------------------------

void TKIBI_LSM6DS3::setAccelerometerReadingSpeed_ms(uint16_t readingSpeed)
{
  accelerometerReadingSpeed_ms = readingSpeed;
}

void TKIBI_LSM6DS3::setGyroscopeReadingSpeed_ms(uint16_t readingSpeed)
{
  gyroscopeReadingSpeed_ms = readingSpeed;
}

void TKIBI_LSM6DS3::setAccelerometerDetectValue(float detectValue)
{
  accelerometer->setDetectValue(detectValue);
}

void TKIBI_LSM6DS3::setGyroscopeDetectValue(float detectValue)
{
  gyroscope->setDetectValue(detectValue);
}

//-------------------------------- PRIVATES --------------------------------

void TKIBI_LSM6DS3::getDistanceVector3(Vector3* distance)
{
  double distance_x = getDistance(distance->getX());
  double distance_z = getDistance(distance->getY());
  double distance_y = getDistance(distance->getZ());

  distance->set(distance_x, distance_y, distance_z);
} 

double TKIBI_LSM6DS3::getDistance(double acceleration)
{
  static double speed = 0;

  double sensorReadingSpeed_s = accelerometerReadingSpeed_ms / 1000.0;
  double accelerationPer_s = acceleration * sensorReadingSpeed_s;

  speed += accelerationPer_s;
  return speed * accelerometerReadingSpeed_ms;
}

void TKIBI_LSM6DS3::setup_Sensor()
{
  status_t status = IMU->begin();

  switch(status)
  {
    case IMU_SUCCESS:
      Serial.println("[IMU_succes] SUCCES initializing the accelerometer/gyro sensors");
      break;

    case IMU_HW_ERROR:
      Serial.println("[IMU_hw_error] FAILED initializing the accelerometer/gyro sensors, because of hardware an error(failed to readRegister)!!");
      exit(0);
      break;

    default:
      Serial.println("[IMU_unkown_error] FAILED initializing the accelerometer/gyro sensor, for unkown reasons!!");
      exit(0);
      break;
  }
}
