#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include <vecmath.h>
#include <float.h>
#include <cmath>

#define M_PI 3.14159265

class Camera
{
public:
	//generate rays for each screen-space coordinate
	virtual Ray generateRay( const Vector2f& point ) = 0 ; 
	
	virtual float getTMin() const = 0 ; 
	virtual ~Camera(){}
protected:
	Vector3f center; 
	Vector3f direction;
	Vector3f up;
	Vector3f horizontal;

};

///TODO: Implement Perspective camera
///Fill in functions and add more fields if necessary
class PerspectiveCamera: public Camera
{
public:
	PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle) {
		this->center = center;
		this->direction = direction.normalized();
		Vector3f u = Vector3f::cross(direction, up).normalized();
		Vector3f v = Vector3f::cross(u, direction).normalized();
		this->horizontal = u;
		this->up = v;
		this->dist = 1.f/tan(angle/2.f);
	}

	virtual Ray generateRay( const Vector2f& point){
		assert(point.x() >= -1.f && point.x() <= 1.f
			&& point.y() >= -1.f && point.y() <= 1.f);

		Vector3f orig = center;
		Vector3f dir = dist * direction 
			+ point[0]*horizontal
			+ point[1]*up; // need to * aspect

		return Ray(orig, dir);
	}

	virtual float getTMin() const { 
		return 0.0f;
	}

private:
	float dist;
	// float aspect; <= 1 for square 

};

#endif //CAMERA_H
