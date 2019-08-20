#ifndef INFERNO_DISPLAY_DISPLAYINTERFACE_H_
#define INFERNO_DISPLAY_DISPLAYINTERFACE_H_

#include "../common.hpp"

class Pixel;

class DisplayInterface {
public: 
    DisplayInterface();

    bool Active = false;
    int XRes, YRes;
    std::string Title;
    unsigned int Scale = 1;
    
    uint32_t* Framebuffer;

    virtual bool Init() = 0;

    virtual void SetPixel(int x, int y, Pixel p) = 0;
    virtual void SetPixel(int x, int y, uint32_t p) = 0;
    virtual void SetPixelSafe(int x, int y, Pixel p) = 0;
    virtual void SetPixelSafe(int x, int y, uint32_t p) = 0;

    virtual void Update() = 0;
	virtual void UpdatePartial() = 0;

    virtual void Close() = 0;
};

#endif
