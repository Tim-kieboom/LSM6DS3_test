#include "TKIBI_LSM6DS3.h"
#define NEW_VALUE(vector3) vector3.nonZeroValue()
#define GET_GRAVITYCONSTANT gravityCalibration->replace(accelerometer->calibrateGravityAccelerometer())

//---------------- CONSTRUCTORS ----------------

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

//---------------- EVENTS ----------------

void TKIBI_LSM6DS3::start()
{
  GET_GRAVITYCONSTANT;
  timer.startTimer();
}

void TKIBI_LSM6DS3::reset()
{
  delete IMU;
  IMU = new LSM6DS3(I2C_MODE, 0x6A);

  timer.startTimer();
  GET_GRAVITYCONSTANT;

  distanceMoved->replace(new Vector3());
}

//---------------- SENSOR_DATA ----------------

void TKIBI_LSM6DS3::checkIfDistanceMoved()
{
  if(timer.wait_ms(accelerometerReadingSpeed_ms))
  {
    Vector3* accelerations = new Vector3();

    accelerometer->getAcceleration(/*out*/ accelerations, gravityCalibration);
    accelerations->print();
    
    // Vector3* gyro = gyroscope->readGyroscope();
    // gyro->print();
    // delete gyro;

    // getDistanceVector3(/*out*/ accelerations);

    // Vector3* tempDist = distanceMoved->add(accelerations);
    // distanceMoved->replace(tempDist);

    // Serial.print("distance: ");
    // distanceMoved->print();
    // Serial.println("");

    delete accelerations;
    // delete tempDist;
  }

  timer.updateNow();
}

void TKIBI_LSM6DS3::printRawData()
{
  Vector3* rawAcclrData = accelerometer->readAccelerometer();
  Vector3* rawGyroData = gyroscope->readGyroscope();

  Serial.println("Accelerometer raw data:");
  rawAcclrData->print();
  Serial.println();

  Serial.println("Gyroscop raw data:");
  rawGyroData->print();
  Serial.println();

  delete rawAcclrData;
  delete rawGyroData;
}

Vector3* TKIBI_LSM6DS3::getRawAccelerometerData()
{
  return accelerometer->readAccelerometer(); 
}

Vector3* TKIBI_LSM6DS3::getRawGyroscopeData()
{
  return gyroscope->readGyroscope();
}

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

//---------------- PRIVATES ----------------

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
