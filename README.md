# Inferno Pathtracer
[![Build Status](https://travis-ci.org/plane000/inferno.png?branch=master)](https://travis-ci.org/plane000/inferno)

Inferno is a CPU-Only, progressive, unidirectional pathtracing engine written in C++. 

![Latest Render](https://imgur.com/WPs7jjr.jpg)

### Features

* Supports OBJ Files
* Supports many material properties
* Uses multiple types of acceleration structures
* Fully capable GUI adds many runtime customizations to the scene and render settings
* Custom threadpool for best performance

### Build Instructions

```
git clone https://github.com/plane000/inferno
cd inferno
mkdir build
cd build
cmake ..
make
```

### Examples

There are many example scenes that I have made already. Just modify the CurrentTest variable inside the CMakeLists.txt to the name of the file you wish to demo.

### Basic Scene

The basic use of the API is demonstrated below. More documentation will come once the project is more mature.

```cpp
#include "../src/inferno.hpp"

static const int width = 1000;
static const int height = 1000;

int main(int argc, char** argv) {
      InfernoEngine inferno;

      inferno.SetMode(MODE_OPERATION_PROGRESSIVE_GUI);

      inferno.InitWindow(width, height);
    
      Scene* scene = new Scene(width, height);
      scene->sky = new SolidColourSky({ 0.0f, 0.0f, 0.0f } 0.0f);
      scene->camera = new Camera(width, height);
	
      // Light
      Sphere light({ 35.0f, 56.0f, 25.0f }, 35.0f, new Material({ 1.0f, 1.0f, 1.0f }, 0.0f, 5.0f));
      scene->objects.push_back(&light);
	
      Sphere sphere({ 0.0f, 0.0f, -8.0f }, 1.0f, new Material({ 0.817f, 0.374, 0.574 }, 0.5f));
      scene->objects.push_back(&sphere);

      Plane plane({ 0.0f,-1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, new Material({ 0.9f, 0.9f, 0.9f }, 0.0f));
      scene->objects.push_back(&plane);

      inferno.SetScene(scene);

      inferno.Ready();
      inferno.Render();

      return 0;
}
```
![Example Render](https://imgur.com/ueTC3OS.png)

### References

While I have been working on this project, I have found a few resources to be especially useful. Below are a few I have listed.

* [Scratch A Pixel - Global Illumination](https://www.scratchapixel.com)

### Samples

![Stanford Dragon](https://imgur.com/WPs7jjr.jpg)
![Stanford Dragon](https://imgur.com/POj0JlL.png)
![Cornell Box Specular Materials](https://imgur.com/wfOieEk.png)
![Cornell Box](https://imgur.com/i4hLxra.png)
![Cornell Box No Colours](https://imgur.com/u2sIKxK.png)
