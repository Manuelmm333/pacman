#include "ModManager.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
using DynamicLibraryHandle = HINSTANCE;

inline DynamicLibraryHandle LoadDynamicLibrary(const std::string& path) {
    return LoadLibraryEx(path.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
}

inline void* GetSymbol(DynamicLibraryHandle handle, const std::string& symbol) {
    return reinterpret_cast<void*>(GetProcAddress(handle, symbol.c_str()));
}

inline void UnloadDynamicLibrary(DynamicLibraryHandle handle) {
    if (!FreeLibrary(handle)) {
        std::cerr << "Failed to unload library: " << GetLastError() << std::endl;
    }
}
#else // Linux
#include <dlfcn.h>
using DynamicLibraryHandle = void*;

DynamicLibraryHandle LoadDynamicLibrary(const std::string& path) {
    return dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
}

void* GetSymbol(DynamicLibraryHandle handle, const std::string& symbol) {
    return dlsym(handle, symbol.c_str());
}

void UnloadDynamicLibrary(DynamicLibraryHandle handle) {
    if (dlclose(handle) != 0) {
        std::cerr << "Failed to unload library: " << dlerror() << std::endl;
    }
}
#endif // end _WIN32

ModManager& ModManager::getInstance() {
    static ModManager instance;
    return instance;
}

void ModManager::loadMod(const std::string& modName) {
    std::string dllPath = "lib" + modName + ".dll";
    //HMODULE hModule = LoadLibraryA(dllPath.c_str());
    DynamicLibraryHandle hModule = LoadDynamicLibrary(dllPath);
    if (hModule) {
        //auto loadModFunc = (void(*)(Entity*))GetProcAddress(hModule, "loadMod");
        auto loadModFunc = (void(*)(Entity*))GetSymbol(hModule, "loadMod");
        if (loadModFunc) {
            Mod mod;
            mod.handle = hModule;
            mod.modFunction = loadModFunc;
            m_mods.push_back(mod);
            m_modNames.push_back(modName);
            std::cout << "Loaded mod: " << modName << std::endl;
        }
        else
        {
            std::cout << "Error : Loaded mod: " << modName << std::endl;
        }
    }
    else
    {
        std::cout << "Error : Loaded mod: " << modName << std::endl;
    }
    
}

void ModManager::applyMods(Entity* entity, const std::string& specificMod) {
    if (!entity) return;
    
    for (size_t i = 0; i < m_mods.size(); ++i) {
        if (specificMod.empty() || m_modNames[i] == specificMod) {
            m_mods[i].modFunction(entity);
        }
    }
}

void ModManager::unloadMods() {
    for (auto& mod : m_mods) {
        //FreeLibrary(mod.handle);
        UnloadDynamicLibrary(mod.handle);
    }
    m_mods.clear();
    m_modNames.clear();
}

ModManager::~ModManager() {
    unloadMods();
} 