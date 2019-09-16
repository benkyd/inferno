#ifndef INFERNO_COMMON_H_
#define INFERNO_COMMON_H_

#if _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>

#include <iostream>
#include <string>

enum OperationMode {
    MODE_OPERATION_PROGRESSIVE_GUI,
    MODE_OPERATION_PROGRESSIVE_IMG,
    MODE_OPERATION_SAMPLES_IMG,
};

enum AccelerationMode {
    MODE_ACCELERATION_NONE,
    MODE_ACCELERATION_KD,
    MODE_ACCELERATION_KD_SLOW,
    MODE_ACCELERATION_BVH,
};

enum RenderMode {
	MODE_RENDER_PATHTRACE,
	MODE_RENDER_NORMALS,
	MODE_RENDER_PATH_BOUNCES,
	MODE_RENDER_PATH_LENGTH
};

enum ToneMapMode {
	MODE_TONEMAP_REINHARD,
	MODE_TONEMAP_EXP,
	MODE_TONEMAP_CLAMP,
	MODE_TONEMAP_BASIC
};

#endif
