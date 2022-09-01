#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vecmath.h>
#include "Object3D.h"
#include "util.h"
#include <iostream>
///TODO implement this class
///So that the intersect function first transforms the ray
///Add more fields as necessary
class Transform: public Object3D
{
public: 
  Transform(){}
 Transform( const Matrix4f& m, Object3D* obj ):o(obj) {
    bool flag = 0;
    M_world2obj = m.inverse(&flag);
    assert(flag == 0);
    // std::cerr << M_obj2world << M_world2obj;
  }
  ~Transform(){
  }
  virtual bool intersect( const Ray& r , Hit& h , float tmin){
    Vector4f orig(r.getOrigin(), 1.f);
    Vector4f dir(r.getDirection(), 0.f);
    Ray localRay((M_world2obj * orig).xyz(), (M_world2obj * dir).xyz() );

    if (o->intersect( localRay, h, tmin)) {
      // update hit with new normal
      Vector4f n_os(h.getNormal(), 0.f);
      Vector3f n_ws = (M_world2obj.transposed() * n_os).xyz().normalized();
      h.set(h.getT(), h.getMaterial(), n_ws);
      return true;
    }
    return false;

  }

 protected:
  Object3D* o; //un-transformed object
  // Matrix4f M_obj2world; <- unnessary in this assignment
  Matrix4f M_world2obj;
};

#endif //TRANSFORM_H
