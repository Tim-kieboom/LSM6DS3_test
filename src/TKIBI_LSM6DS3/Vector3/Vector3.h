#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

#include "Arduino.h"

class Vector3
{
private:
  double x, y, z;

public:
  Vector3();
  Vector3(double x, double y, double z);
  Vector3(double* array);
  Vector3(Vector3* vector);

  Vector3 operator+(Vector3   other);
  Vector3 operator+(double    other);
  double* operator+(double*   array);
  Vector3*      add(Vector3*  other);

  Vector3 operator-(Vector3   other);
  Vector3 operator-(double    other);
  double* operator-(double*   array);
  Vector3* subtract(Vector3*  other);

  Vector3 operator*(Vector3   other);
  Vector3 operator*(double    other);
  double* operator*(double*   array);
  Vector3* multiply(double    other);

  Vector3 operator/(Vector3   other);
  Vector3 operator/(double    other);
  double* operator/(double*   array);
  Vector3*   divide(Vector3*  other);


  bool nonZeroValue();

  void print();

  void  set(double x, double y, double z);
  void  set(double* array);
  void  set(Vector3* vector);
  void  set(Vector3 vector);

  void setX(double x);
  void setY(double y);
  void setZ(double z);

  Vector3 copy();
  void replace(Vector3* pointer);
  
  double* getArray();
  Vector3* getPointer();
  double  getX();
  double  getY();
  double  getZ();
};

#endif