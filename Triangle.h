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


		// solving Barycentric equation
		bool isSingular = 0;
		Matrix3f M(a_b, a_c, ray.getDirection());
		Matrix3f M_inv = M.inverse(&isSingular);

		if(isSingular) {
			// ray is parallel to the plane
			return false;
		}
		// param = {beta, gamma, t}
		Vector3f param = M_inv * (a - ray.getOrigin());
		float &beta = param[0], &gamma = param[1], &t = param[2];

		// validate
		if(isConvex(beta, gamma) && t >= tmin && t < hit.getT()) {
			float alpha = 1 - beta - gamma;

			Vector3f norm = alpha * normals[0] + beta * normals[1] + gamma * normals[2];
			hit.set(t, material, norm);
			
			Vector2f texCoord = alpha * texCoords[0] + beta * texCoords[1] + gamma * texCoords[2];
			hit.setTexCoord(texCoord);
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
		return (beta >= 0 && gamma >= 0 && beta + gamma <= 1);
	}

};

#endif //TRIANGLE_H
