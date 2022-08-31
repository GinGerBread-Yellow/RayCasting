#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vecmath.h>

using namespace std;

inline ostream& operator << (ostream &os, const Vector2f &f) {
  os << '<' << f[0] << ',' << f[1] << '>';
  return os;
}

inline ostream& operator << (ostream &os, const Vector3f &f) {
  os << '<' << f[0] << ',' << f[1] << ',' << f[2] << '>';
  return os;
}

inline ostream& operator << (ostream &os, const Vector4f &f) {
  os << '<' << f[0] << ',' << f[1] << ',' << f[2] << ',' << f[3] << '>';
  return os;
}

inline ostream& operator << (ostream &os, const Matrix4f &mat) {
  os << "matrix\t" << mat.getRow(0) << '\n'
    << '\t' << mat.getRow(1) << '\n'
    << '\t' << mat.getRow(2) << '\n'
    << '\t' << mat.getRow(3) << '\n';
  return os;
}

#endif // UTIL_H
