#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object3D.h"
#include <vecmath.h>
#include <cmath>
#include <iostream>

using namespace std;
///TODO: implement this class.
///Add more fields as necessary,
///but do not remove hasTex, normals or texCoords
///they are filled in by other components
class Triangle: public Object3D
{
public:
	Triangle();
        ///@param a b c are three vertex positions of the triangle
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m):Object3D(m){
          hasTex = false;
          this->a = a;
          this->a_b = a - b;
          this->a_c = a - c;
	}

	virtual bool intersect( const Ray& ray,  Hit& hit , float tmin){
		Matrix3f M(a_b, a_c, ray.getDirection());
		bool isSingular = 0;
		Matrix3f M_inv = M.inverse(&isSingular);
		if(isSingular) {
			// ray is parallel to the plane
			return false;
		}
		// param = {beta, gamma, t}
		Vector3f param = M_inv * (a - ray.getOrigin());

		// validate
		if(isConvex(param[0], param[1]) 
				&& param[2] >= tmin && param[2] < hit.getT()) {
			hit.set(param[2], material, Vector3f::cross(a_b, a_c).normalized());
			return true;
		}
		return false;
	}
	bool hasTex;
	Vector3f normals[3];
	Vector2f texCoords[3];
protected:
	Vector3f a;
	Vector3f a_b;
	Vector3f a_c;

	inline bool isConvex(float beta, float gamma) {
		return (beta >= 0 && beta <= 1 
			&& gamma >= 0 && gamma <= 1 
			&& beta + gamma <= 1);
	}

};

#endif //TRIANGLE_H
