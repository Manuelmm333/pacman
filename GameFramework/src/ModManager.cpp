#include "ModManager.h"
#include <Windows.h>
#include <iostream>

ModManager& ModManager::getInstance() {
    static ModManager instance;
    return instance;
}

void ModManager::loadMod(const std::string& modName) {
    std::string dllPath = "lib" + modName + ".dll";
    HMODULE hModule = LoadLibraryA(dllPath.c_str());
    if (hModule) {
        auto loadModFunc = (void(*)(Entity*))GetProcAddress(hModule, "loadMod");
        if (loadModFunc) {
            Mod mod;
            mod.handle = hModule;
            mod.modFunction = loadModFunc;
            m_mods.push_back(mod);
            m_modNames.push_back(modName);
            std::cout << "Loaded mod: " << modName << std::endl;
        }
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
        FreeLibrary(mod.handle);
    }
    m_mods.clear();
    m_modNames.clear();
}

ModManager::~ModManager() {
    unloadMods();
} 