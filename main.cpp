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
#include "util.h"

using namespace std;

float clampedDepth ( float depthInput, float depthMin , float depthMax);

struct Config {
  char *inputfile = 0;
  char *outputfile = 0;
  char *depthfile = 0;
  int width = 64;
  int height = 64;
  float dmin = 0.f;
  float dmax = 0.f;
};

void parseConfig(int, char *[], struct Config&);

#include "bitmap_image.hpp"
int main( int argc, char* argv[] )
{
  
  struct Config config;
  parseConfig(argc, argv, config);
  // First, parse the scene using SceneParser.
  // Then loop over each pixel in the image, shooting a ray
  // through that pixel and finding its intersection with
  // the scene.  Write the color at the intersection to that
  // pixel in your output image.
  
  SceneParser scene(config.inputfile);

  Image image( config.width , config.height );

  Camera *camera = scene.getCamera();
  Group *group = scene.getGroup();
  float tmin = camera->getTMin();

  float deltaX = (float)2/(config.width-1);
  float deltaY = (float)2/(config.height-1); 
  for (int i = 0; i < config.width; i++) {
    for (int j = 0; j < config.height; j++) {

      Vector2f pixel(deltaX*i-1, deltaY*j-1);
      Ray ray = camera->generateRay(pixel);
      // cerr << "ray :" << ray.getDirection()[0] << ' '
      //   << ray.getDirection()[1] << ' '
      //   << ray.getDirection()[2] << '\n';


      Hit hit;
      Vector3f pixelColor = scene.getAmbientLight();
      if (group->intersect(ray, hit, tmin)) {
        // shading
        // Vector3f norm = hit.getNormal();
        Material *material = hit.getMaterial();
        pixelColor = material->getDiffuseColor();

        // for (int l = 0, nlight = scene.getNumLights(); l < nlight; l++) {
        //   Light* light = scene.getLight(l);
        //   Vector3f dir2Light, lightColor, p = ray.getOrigin()+hit.getT()*ray.getDirection();
        //   float dist;
        //   light->getIllumination(p,dir2Light, lightColor, dist);
        //   pixelColor += texture->Shade(ray, hit, dir2Light, lightColor);
        // }

      }
      image.SetPixel( i, j, pixelColor );
    }
  }
  image.SaveImage(config.outputfile);
  return 0;
}


void parseConfig(int argc, char *argv[], struct Config& config ) {
  // Fill in your implementation here.

  // This loop loops over each of the input arguments.
  // argNum is initialized to 1 because the first
  // "argument" provided to the program is actually the
  // name of the executable (in our case, "a4").
  // for( int argNum = 1; argNum < argc; ++argNum )
  // {
  //   std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
  // }

  int idx = 1;
  while(idx < argc) {
    char *arg = argv[idx];
    if (!strcmp(arg, "-input")) {
      config.inputfile = argv[idx+1];
      idx += 2;
    } else if (!strcmp(arg, "-output")) {
      config.outputfile = argv[idx+1];
      idx += 2;
    } else if (!strcmp(arg, "-depth")) {
      config.dmin = stof(argv[idx+1]);
      config.dmax = stof(argv[idx+2]);
      config.depthfile = argv[idx+3];
      idx += 4;
    } else if (!strcmp(arg, "-size")) {
      config.width = stoi(argv[idx+1]);
      config.height = stoi(argv[idx+2]);
      idx += 3;
    } else {
      cerr << "errror arg: " << arg << '\n';
      idx++;
    }
  }
  char *error = "n/a";

#define PRINT_NAME(filename, err) ((filename)? filename : err)

  cerr << "Config:\n"
    << "\tinputfile = " << PRINT_NAME(config.inputfile, error) << '\n'
    << "\tdepthfile = " << PRINT_NAME(config.depthfile, error) << '\n'
    << "\toutputfile = " << PRINT_NAME(config.outputfile, error) << '\n'
    << "\twidth = " << config.width << '\n'
    << "\theight = " << config.height << '\n'
    << "\tdmin = " << config.dmin << '\n'
    << "\tdmax = " << config.dmax << '\n';

}



