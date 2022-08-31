#ifndef GROUP_H
#define GROUP_H


#include "Object3D.h"
#include "Ray.h"
#include "Hit.h"
#include <iostream>

using  namespace std;

///TODO: 
///Implement Group
///Add data structure to store a list of Object* 
class Group:public Object3D
{
public:

  Group():size(0){

  }
	
  Group( int num_objects ):size(num_objects), objects(num_objects, 0) {

  }

  ~Group(){
    for(int i = 0; i < size; i++) {
      if(objects[i]) delete objects[i];
      objects[i] = 0;
    }
  }

  virtual bool intersect( const Ray& r , Hit& h , float tmin ) {
		  bool flag = false;
      // cerr << "ret =";
      for (int i = 0; i < size; i++) {
        if(objects[i]) {
          bool tmp = objects[i]->intersect(r, h, tmin);
          flag |= tmp;
          // cerr << tmp;
        }
      }
      // cerr << '\n';
      return flag;
   }
	
  void addObject( int index , Object3D* obj ){
    objects[index] = obj;
  }

  int getGroupSize(){ 
    return size;
  }

 private:

  int size;
  vector<Object3D*> objects;

};

#endif
	
