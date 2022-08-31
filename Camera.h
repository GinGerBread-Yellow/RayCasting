#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"
#include <vecmath.h>
#include <float.h>
#include <cmath>


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
	PerspectiveCamera(const Vector3f& center, const Vector3f& direction,const Vector3f& up , float angle): FoV(angle) {
		this->center = center;
		this->direction = direction;
		Vector3f u = Vector3f::cross(direction, up);
		Vector3f v = Vector3f::cross(u, direction);
		this->horizontal = u;
		this->up = v;
	}

	virtual Ray generateRay( const Vector2f& point){

		Vector3f orig = center;
		Vector3f dir = direction + point[0]*horizontal + point[1]*up;
		return Ray(orig, dir);
	}

	virtual float getTMin() const { 
		return 0.0f;
	}

private:

	float FoV;

};

#endif //CAMERA_H
