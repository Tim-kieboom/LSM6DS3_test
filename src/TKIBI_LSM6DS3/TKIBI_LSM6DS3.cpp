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

TKIBI_LSM6DS3::TKIBI_LSM6DS3(double initialSpeed)
: initialSpeed(initialSpeed)
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

TKIBI_LSM6DS3::TKIBI_LSM6DS3(uint16_t accelerometerReadingSpeed_ms, uint16_t gyroscopeReadingSpeed_ms, double initialSpeed)
: accelerometerReadingSpeed_ms(accelerometerReadingSpeed_ms), gyroscopeReadingSpeed_ms(gyroscopeReadingSpeed_ms), initialSpeed(initialSpeed)
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
  if(GYRO_TIMER)
  {
    gyroscope->getAngularAcceleration(/*out*/ gyroAccelerations);
  }

  if(ACCELEROMETER_TIMER)
  {
    uint64_t sensorTime = millis();
    Vector3* prevDistanceMoved = distanceMoved->copyPointer();

    accelerometer->getAcceleration(/*out*/ accelerations, gravityCalibration);
    getDistanceVector3(/*out*/ accelerations, sensorTime);

    distanceMoved = distanceMoved->add(accelerations);

    accelerations->print("accl");

    Serial.print("distance: ");
    distanceMoved->print();
    Serial.println("");

    delete prevDistanceMoved;
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
  Vector3* rawAcclrData = accelerometer->rawReading();

  Serial.println("Accelerometer raw data:");
  rawAcclrData->print();
  Serial.println();

  delete rawAcclrData;
}
void TKIBI_LSM6DS3::printRawGyroscopeData()
{
  Vector3* rawGyroData = gyroscope->rawReading();

  Serial.println("Gyroscop raw data:");
  rawGyroData->print();
  Serial.println();

  delete rawGyroData;
}

void TKIBI_LSM6DS3::printData()
{
  printAccelerometerData();
  printGyroscopeData();
}

void TKIBI_LSM6DS3::printAccelerometerData()
{
  Vector3* rawAcclrData = accelerometer->readAccelerometer();

  Serial.println("Accelerometer raw data:");
  rawAcclrData->print();
  Serial.println();

  delete rawAcclrData;
}

void TKIBI_LSM6DS3::printGyroscopeData()
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

Accelerometer* TKIBI_LSM6DS3::getAccelerometer()
{
  return accelerometer;
}

Gyroscope* TKIBI_LSM6DS3::getGyroscope()
{
  return gyroscope;
}

double TKIBI_LSM6DS3::getCurrentSpeed()
{
  return initialSpeed;
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

void TKIBI_LSM6DS3::setCurrentSpeed(double initialSpeed)
{
  this->initialSpeed = initialSpeed;
}

//-------------------------------- PRIVATES --------------------------------


void TKIBI_LSM6DS3::getDistanceVector3(Vector3* distance, uint64_t beginReadingTime)
{
  uint64_t sensorReadingTime = beginReadingTime - millis();

  double distance_x = getDistance(distance->getX(), sensorReadingTime);
  double distance_y = getDistance(distance->getY(), sensorReadingTime);
  double distance_z = getDistance(distance->getZ(), sensorReadingTime);

  distance->set(distance_x, distance_y, distance_z);
} 


double TKIBI_LSM6DS3::getDistance(double acceleration, uint64_t sensorReadingTime)
{
  /*
    the formula is:
    D = v*t + 1/2 * a * t^2

    D = distance (in meters)
    v = velocity (in m/s)
    a = acceleration (in m/s^2)
    t = time (in seconds)
  */

  //add the time it takes to read the acceleration plus the wait time between readings
  uint64_t totalTime_milieSeconds = sensorReadingTime + (uint64_t)accelerometerReadingSpeed_ms;
  double totalTime = (double)totalTime_milieSeconds / 1000.0;

  // newSpeed = 1/2 * a * t^2
  double newSpeed = (double)0.5 * acceleration * pow(totalTime, 2);
  //distance = v*t + 1/2 * a * t^2
  double distance = (initialSpeed * totalTime) + newSpeed;

  initialSpeed = newSpeed;

  return distance;
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
