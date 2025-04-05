#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "Entity.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

class ModManager {
public:
    static ModManager& getInstance();
    
    void loadMod(const std::string& modPath);
    void unloadMods();
    void applyMods(Entity* entity);
    
private:
    ModManager() = default;
    ~ModManager();
    ModManager(const ModManager&) = delete;
    ModManager& operator=(const ModManager&) = delete;
    
    struct Mod {
#ifdef _WIN32
        HMODULE handle;
#else
        void* handle;
#endif
        std::function<void(Entity*)> modFunction;
    };
    
    std::vector<Mod> m_mods;
}; 