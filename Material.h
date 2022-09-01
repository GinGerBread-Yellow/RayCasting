#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>
#include <iostream>
#include "util.h"

#include "Ray.h"
#include "Hit.h"
#include "texture.hpp"
///TODO:
///Implement Shade function that uses ambient, diffuse, specular and texture
class Material
{
public:
	
 Material( const Vector3f& d_color ,const Vector3f& s_color=Vector3f::ZERO, float s=0):
  diffuseColor( d_color),specularColor(s_color), shininess(s)
  {
        	
  }

  virtual ~Material()
    {

    }

  virtual Vector3f getDiffuseColor() const 
  { 
    return  diffuseColor;
  }
    

  Vector3f Shade( const Ray& ray, const Hit& hit,
                  const Vector3f& dirToLight, const Vector3f& lightColor ) {

#define clamp(x) (max(0.f, x)) // (max(0.f, min(1.f, x)))

    Vector3f diffuse;
    Vector3f specular;
    // find R
    // assert(Vector3f::dot(ray.getDirection(), hit.getNormal()) < 0);
    float nDotd = Vector3f::dot(ray.getDirection(), hit.getNormal());
    Vector3f reflect = (ray.getDirection() 
                          - 2.f * nDotd * hit.getNormal()).normalized();




    // diffusion color 
    float lDotn = clamp(Vector3f::dot(dirToLight, hit.getNormal()));
    if(t.valid()) {
      // texture
      Vector3f textureColor = t(hit.texCoord[0], hit.texCoord[1]);
      diffuse = lDotn * textureColor * lightColor;
      diffuseColor = textureColor;
    } else
      diffuse = lDotn * diffuseColor * lightColor;

    // specular color
    float lDotr = clamp(Vector3f::dot(dirToLight, reflect));
    specular = pow(lDotr, shininess) * specularColor * lightColor;

    // net color
    Vector3f color = diffuse + specular;


    // cerr << "lr, ln:" << lr << ',' << ln << '\n' 
    //   <<"diffuse " << dif << '\n'
    //   << "specularColor:" << spec << '\n'
    //   << "color: " << color << '\n';
    return color; 
		
  }

  void loadTexture(const char * filename){
    t.load(filename);
  }


 protected:
  Vector3f diffuseColor;
  Vector3f specularColor;
  float shininess;
  Texture t;
};



#endif // MATERIAL_H
