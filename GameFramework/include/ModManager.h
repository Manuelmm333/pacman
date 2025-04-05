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
    
    void loadMod(const std::string& modName);
    void applyMods(Entity* entity, const std::string& specificMod = "");
    void unloadMods();
    ~ModManager();
    
private:
    ModManager() = default;
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
    std::vector<std::string> m_modNames;
}; 