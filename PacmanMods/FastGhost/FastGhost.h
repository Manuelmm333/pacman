#pragma once
#include "Entity.h"

#ifdef _WIN32
extern "C" __declspec(dllexport) void loadMod(Entity* entity); 
#else
extern "C" __attribute__((visibility("default"))) void loadMod(Entity* entity);
#endif