#include "ModManager.h"
#include <iostream>

ModManager& ModManager::getInstance() {
    static ModManager instance;
    return instance;
}

void ModManager::loadMod(const std::string& modPath) {
#ifdef _WIN32
    HMODULE handle = LoadLibraryA(modPath.c_str());
    if (!handle) {
        std::cerr << "Error loading mod: " << GetLastError() << std::endl;
        return;
    }
#else
    void* handle = dlopen(modPath.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error loading mod: " << dlerror() << std::endl;
        return;
    }
#endif

    typedef void(*ModFunction)(Entity*);
#ifdef _WIN32
    ModFunction modFunc = (ModFunction)GetProcAddress(handle, "loadMod");
#else
    ModFunction modFunc = (ModFunction)dlsym(handle, "loadMod");
#endif

    if (!modFunc) {
        std::cerr << "Error getting mod function" << std::endl;
#ifdef _WIN32
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
        return;
    }

    m_mods.push_back({handle, modFunc});
    std::cout << "Mod loaded successfully: " << modPath << std::endl;
}

void ModManager::unloadMods() {
    for (auto& mod : m_mods) {
#ifdef _WIN32
        FreeLibrary(mod.handle);
#else
        dlclose(mod.handle);
#endif
    }
    m_mods.clear();
}

void ModManager::applyMods(Entity* entity) {
    for (auto& mod : m_mods) {
        mod.modFunction(entity);
    }
}

ModManager::~ModManager() {
    unloadMods();
} 