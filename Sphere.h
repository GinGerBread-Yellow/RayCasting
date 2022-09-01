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
		// assert(this->center == center);
		// assert(this->radius == radius);
		// cerr << "init sphere with " << center[0] << ',' <<
		// 	center[1] << ',' << center[2] << ' ' << radius << '\n';
	}
	

	~Sphere(){}

	virtual bool intersect( const Ray& r , Hit& h , float tmin){


		Vector3f orig = r.getOrigin() - center;
		Vector3f dir = r.getDirection();

		// solving quadratic function
		float a = dir.absSquared();
		float b = 2.f * Vector3f::dot(orig, dir);
		float c = orig.absSquared() - radius*radius;

		float det = b * b - 4.f * a * c;

		if(det < 0) return false;

		float d = sqrt(det);
		float t1 = (-b - d) / (2.f*a);
		float t2 = (-b + d) / (2.f*a);

		// t1 <= t2
		float t;
		if(t1 >= tmin && t1 < h.getT()) {
			t = t1;
		} else if (t2 >= tmin && t2 < h.getT()) {
			t = t2;
		} else {
			return false;
		}
		// update hit
		Vector3f hitpoint = r.pointAtParameter(t);
		Vector3f normal = (hitpoint - center).normalized();
		h.set(t, material, normal);
		return true;
	}

protected:
	Vector3f	center;
	float			radius;

};


#endif
