#include "Vector3.h"

//-------------------------------- CONSTRUCTORS --------------------------------

Vector3::Vector3()
{ 
    this->set(0,0,0);
}

Vector3::Vector3(double x, double y, double z)
{
    this->set(x, y, z);
}

Vector3::Vector3(double* array)
{
    this->set(array);
}

Vector3::Vector3(Vector3* vector)
{
    this->set(vector);
}

//-------------------------------- OPERATORS --------------------------------

Vector3 Vector3::operator+(Vector3 other)
{
    double _x = x + other.x;
    double _y = y + other.y;
    double _z = z + other.z;

    return Vector3(_x, _y, _z);
}

Vector3 Vector3::operator+(double other)
{
    double _x = x + other;
    double _y = y + other;
    double _z = z + other;

    return Vector3(_x, _y, _z);
}

double* Vector3::operator+(double* array)
{
    array[0] += x;
    array[1] += y;
    array[2] += z;

    return array;
}

Vector3* Vector3::add(Vector3* other)
{
    this->x = x + other->getX();
    this->y = y + other->getY();
    this->z = z + other->getZ();

    return this;
}

Vector3* Vector3::add(double other)
{
    this->x = x + other;
    this->y = y + other;
    this->z = z + other;

    return this;
}



Vector3 Vector3::operator-(Vector3 other)
{
    double _x = x - other.x;
    double _y = y - other.y;
    double _z = z - other.z;

    return Vector3(_x, _y, _z);
}

Vector3 Vector3::operator-(double other)
{
    double _x = x - other;
    double _y = y - other;
    double _z = z - other;

    return Vector3(_x, _y, _z);
}

double* Vector3::operator-(double* array)
{
    array[0] -= x;
    array[1] -= y;
    array[2] -= z;

    return array;
}

Vector3* Vector3::subtract(Vector3* other)
{
    this->x = x - other->getX();
    this->y = y - other->getY();
    this->z = z - other->getZ();

    return this;
}

Vector3* Vector3::subtract(double other)
{
    this->x = x - other;
    this->y = y - other;
    this->z = z - other;

    return this;
}


Vector3 Vector3::operator*(Vector3 other)
{
    double _x = x * other.x;
    double _y = y * other.y;
    double _z = z * other.z;

    return Vector3(_x, _y, _z);
}

Vector3 Vector3::operator*(double other)
{
    double _x = x * other;
    double _y = y * other;
    double _z = z * other;

    return Vector3(_x, _y, _z);
}

double* Vector3::operator*(double* array)
{
    array[0] *= x;
    array[1] *= y;
    array[2] *= z;

    return array;
}

Vector3* Vector3::multiply(Vector3* other)
{
    this->x = x * other->getX();
    this->y = y * other->getY();
    this->z = z * other->getZ();

    return this;
}

Vector3* Vector3::multiply(double other)
{
    this->x = x * other;
    this->y = y * other;
    this->z = z * other;

    return this;
}



Vector3 Vector3::operator/(Vector3 other)
{
    double _x = x / other.x;
    double _y = y / other.y;
    double _z = z / other.z;

    return Vector3(_x, _y, _z);
}

Vector3 Vector3::operator/(double other)
{
    double _x = x / other;
    double _y = y / other;
    double _z = z / other;

    return Vector3(_x, _y, _z);
}

double* Vector3::operator/(double* array)
{
    array[0] /= x;
    array[1] /= y;
    array[2] /= z;

    return array;
}

Vector3* Vector3::divide(Vector3* other)
{
    this->x = x / other->getX();
    this->y = y / other->getY();
    this->z = z / other->getZ();

    return this;
}

Vector3* Vector3::divide(double other)
{
    this->x = x / other;
    this->y = y / other;
    this->z = z / other;

    return this;
}

Vector3* Vector3::average(Vector3* vectorArray[], uint16_t numberOfVectors)
{
    Vector3* addTotal = new Vector3();

    for(uint16_t i = 0; i < numberOfVectors; i++)
    {
        addTotal->add(vectorArray[i]);
    }
    addTotal->divide(numberOfVectors);

    return addTotal;
}

//-------------------------------- PRINT/LOGIC --------------------------------

bool Vector3::nonZeroValue()
{
    return x != 0 && y != 0 && z != 0;
}


void Vector3::print()
{
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(" ,y: ");
    Serial.print(y);
    Serial.print(", z: ");
    Serial.print(z);
    Serial.println();
}

void Vector3::print(String name)
{
    Serial.print("[");
    Serial.print(name);
    Serial.print("] ");
    this->print();
}


//-------------------------------- OBJECT_MANIPULATION --------------------------------

Vector3 Vector3::copy()
{
    return Vector3(x, y, z);
}

 Vector3* Vector3::copyPointer()
{
    return new Vector3(x, y, z);
}

void Vector3::replace(Vector3* pointer)
{
    this->set(pointer);

    delete pointer;
}

//-------------------------------- GETTERS --------------------------------

double* Vector3::getArray()
{
    double* array = new double[3];

    array[0] = x; 
    array[1] = y; 
    array[2] = z;

    return array;
}

Vector3* Vector3::getPointer()
{
    return this;
}

double Vector3::getX()
{
    return x;
}

double Vector3::getY()
{
    return y;
}

double Vector3::getZ()
{
    return z;
}

//-------------------------------- SETTERS --------------------------------

void Vector3::set(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::set(double* array)
{
    this->x = array[0];
    this->y = array[1];
    this->z = array[2];

    delete[] array;
}

void Vector3::set(Vector3* vector)
{
    this->x = vector->getX();
    this->y = vector->getY();
    this->z = vector->getZ();
}

void Vector3::set(Vector3 vector)
{
    this->x = vector.getX();
    this->y = vector.getY();
    this->z = vector.getZ();
}

void Vector3::setX(double x)
{
    this->x = x;
}

void Vector3::setY(double y)
{
    this->y = y;
}

void Vector3::setZ(double z)
{
    this->z = z;
}