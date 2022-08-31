#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "SceneParser.h"
#include "Image.h"
#include "Camera.h"
#include <string.h>

using namespace std;

float clampedDepth ( float depthInput, float depthMin , float depthMax);

#include "bitmap_image.hpp"
int main( int argc, char* argv[] )
{
  // Fill in your implementation here.

  // This loop loops over each of the input arguments.
  // argNum is initialized to 1 because the first
  // "argument" provided to the program is actually the
  // name of the executable (in our case, "a4").
  for( int argNum = 1; argNum < argc; ++argNum )
    {
      std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }
	
    
  // First, parse the scene using SceneParser.
  // Then loop over each pixel in the image, shooting a ray
  // through that pixel and finding its intersection with
  // the scene.  Write the color at the intersection to that
  // pixel in your output image.
  int idx = 1;
  char *input;
  char *output;
  int d1, d2, width, height;
  char *depthmap;
  while(idx < argc) {
    char *arg = argv[idx];
    if (!strcmp(arg, "-input")) {
      input = argv[idx+1];
      idx += 2;
    } else if (!strcmp(arg, "-output")) {
      output = argv[idx+1];
      idx += 2;
    } else if (!strcmp(arg, "-depth")) {
      d1 = stoi(argv[idx+1]);
      d2 = stoi(argv[idx+2]);
      depthmap = argv[idx+3];
      idx += 4;
    } else if (!strcmp(arg, "-size")) {
      width = stoi(argv[idx+1]);
      height = stoi(argv[idx+2]);
      idx += 3;
    } else {
      cerr << "errror arg: " << arg << '\n';
      idx++;
    }
  }
  
  SceneParser scene(input);

 
  ///TODO: below demonstrates how to use the provided Image class
  ///Should be removed when you start
  //width and height
  Image image( width , height );
  Camera *camera = scene.getCamera();
  Group *group = scene.getGroup();
  float tmin = camera->getTMin();
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      // Ray ray = camera->generateRay();
      // Hit hit();
      Vector3f pixelColor(1.f, 0, 0);
      // if (group.intersect(ray, hit, tmin)) {
      //   // shading
      //   Vector3f norm = hit.getNormal();
      //   Material *texture = hit.getMaterial();
      //   for (int l = 0; nlight < scene.getNumLights(); l < nlight; l++) {
      //     Light* light = scene.getLight(l);
      //     Vector3f p, lightDir, lightColor;
      //     float dist;
      //     light->getIllumination(p,lightDir, lightColor, dist);
      //     color += 
      //   }
      // }
      image.SetPixel( i, j, pixelColor );
    }
  }
  image.SaveImage(output);
  return 0;
}

