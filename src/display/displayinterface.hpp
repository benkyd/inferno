#ifndef INFERNO_DISPLAY_DISPLAYINTERFACE_H_
#define INFERNO_DISPLAY_DISPLAYINTERFACE_H_

#include "../common.hpp"
#include "../maths.hpp"

class FrameBuffer;
class Pixel;

class DisplayInterface {
public: 
    DisplayInterface();

    bool Active = false;
	bool ImGui = false;
    int XRes, YRes;
    std::string Title;
	FrameBuffer* Framebuffer;
    
    virtual bool Init() = 0;

	virtual void UpdateTitle(std::string title) = 0;
	virtual void UpdateTitle() = 0;

    virtual void Update() = 0;
	virtual void UpdatePartial() = 0;

    virtual void Close() = 0;
};

#endif
