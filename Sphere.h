#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>

#include <iostream>
using namespace std;
///TODO:
///Implement functions and add more fields as necessary
class Sphere: public Object3D
{
public:
	Sphere():center(0.f), radius(1.f) { 
		//unit ball at the center
	}

	Sphere( Vector3f center , float radius , Material* material ):Object3D(material), center(center), radius(radius) {

	}
	

	~Sphere(){}

	virtual bool intersect( const Ray& r , Hit& h , float tmin){

		Vector3f orig = r.getOrigin();
		Vector3f dir = r.getDirection();
		float a = dir.absSquared();
		float b = 2 * Vector3f::dot(orig, dir);
		float c = orig.absSquared() - radius*radius;

		float det = b * b - 4 * a * c;

		if(det < 0) return false;

		float d = sqrt(det);
		float t1 = (-b - d) / (2*a);
		float t2 = (-b + d) / (2*a);

		if(t1 >= FLT_MAX) return false;
		if(t1 >= h.getT()) return true;

		// t1 <= t2
		float t;
		if(t1 >= tmin && t1 < h.getT()) {
			t = t1;
		} else if (t2 >= tmin && t2 < h.getT()) {
			t = t2;
		} else {
			return false;
		}
		Vector3f hitpoint = orig + t*dir;
		Vector3f normal = (hitpoint - center).normalized();
		h.set(t, material, normal);

		return true;
	}

protected:
	Vector3f	center;
	float			radius;

};


#endif
