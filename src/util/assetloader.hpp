#ifndef INFERNO_UTIL_ASSETLOADER_H_
#define INFERNO_UTIL_ASSETLOADER_H_

#include "../common.hpp"

#include <vector>
#include <string>

class Triangle;

std::vector<Triangle*> LoadTrianglesBasic(std::string path, std::string basePath = "");

#endif
