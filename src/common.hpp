#ifndef INFERNO_COMMON_H_
#define INFERNO_COMMON_H_

#include <SDL2/SDL.h>

#include <iostream>
#include <string>

enum OperationMode {
    MODE_OPERATION_DEFAULT,
    MODE_PROGRESSIVE_GUI,
    MODE_PROGRESSIVE_IMG,
    MODE_SAMPLES_IMG
};

enum AccelerationMode {
    MODE_ACCELERATION_DEFAULT,
    MODE_NONE,
    MODE_KD,
    MODE_KD_SLOW,
    MODE_BVH
};

#endif
