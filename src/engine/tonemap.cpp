#include "tonemap.hpp"

// Need to map a vector of floats to a buffer. need to rework engine first
void MapHRDLDRBasic(uint32_t* buffer, int w, int h) {
	
	for (int x = 0; x < w; x++)
	for (int y = 0; y < h; y++) {

	}
}



int index(int x, int y, int w) {
	return (y * w + x);
}
