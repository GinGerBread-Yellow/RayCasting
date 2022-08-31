#ifndef PLANE_H
#define PLANE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
using namespace std;
///TODO: Implement Plane representing an infinite plane
///choose your representation , add more fields and fill in the functions
class Plane: public Object3D
{
public:
	Plane(){}
	Plane( const Vector3f& normal , float d , Material* m):Object3D(m), offset(-d), normal(normal) {
		// satisfy dot(v, normal) = d

	}
	~Plane(){}
	virtual bool intersect( const Ray& r , Hit& h , float tmin){
		float product = Vector3f::dot(normal, r.getDirection());

		if(product == 0) return false;
		float t = - (offset + Vector3f::dot(normal, r.getOrigin())) / product;

		if( t < tmin) 
			return false;
		else if (t < h.getT()) {
			h.set(t, material, normal);
		}
		return true;

	}

protected:
	float offset;
	Vector3f normal;
};
#endif //PLANE_H
		

