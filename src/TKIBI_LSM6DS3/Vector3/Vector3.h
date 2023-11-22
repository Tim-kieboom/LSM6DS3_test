#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

#include "Arduino.h"

class Vector3
{
private:
  double x, y, z;

public:
//-------------------------------- CONSTRUCTORS --------------------------------


  Vector3();
  Vector3(double x, double y, double z);
  Vector3(double*   array);
  Vector3(Vector3*  vector);


//-------------------------------- OPERATORS --------------------------------


  Vector3 operator+(Vector3   other);
  Vector3 operator+(double    other);
  double* operator+(double*   array);
  Vector3*      add(Vector3*  other);
  Vector3*      add(double    other);

  Vector3 operator-(Vector3   other);
  Vector3 operator-(double    other);
  double* operator-(double*   array);
  Vector3* subtract(Vector3*  other);
  Vector3* subtract(double    other);

  Vector3 operator*(Vector3   other);
  Vector3 operator*(double    other);
  double* operator*(double*   array);
  Vector3* multiply(Vector3*  other);
  Vector3* multiply(double    other);

  Vector3 operator/(Vector3   other);
  Vector3 operator/(double    other);
  double* operator/(double*   array);
  Vector3*   divide(Vector3*  other);
  Vector3*   divide(double    other);

  //get aan array of vector3 objects and calulates the average vector3 and returns it 
  Vector3* average(Vector3* vectorList[], uint16_t numberOfVectors);


//-------------------------------- PRINT/LOGIC --------------------------------

  //returns true if all values are zero
  bool nonZeroValue();

  void print();
  void print(String name);


//-------------------------------- OBJECT_MANIPULATION --------------------------------

  //return new vector3 object with the same values as this vector
  Vector3 copy();

  //return new vector3 POINTER object with the same values as this vector
  Vector3* copyPointer();

  //sets the values in pointer to this vector and then deletes pointer
  void replace(Vector3* pointer);


//-------------------------------- GETTERS --------------------------------
  
  //get an array of x,y,z
  double* getArray();
  //get this
  Vector3* getPointer();

  double  getX();
  double  getY();
  double  getZ();


//-------------------------------- SETTERS --------------------------------


  void  set(double x, double y, double z);
  void  set(double* array);
  void  set(Vector3* vector);
  void  set(Vector3 vector);

  void setX(double x);
  void setY(double y);
  void setZ(double z);
};

#endif