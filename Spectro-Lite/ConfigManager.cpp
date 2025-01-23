#include "ConfigManager.h"
#include "json.hpp"
#include <fstream>
#include <filesystem>
#include "ShlObj.h"
#include <windows.h>

namespace fs = std::filesystem;

std::vector<std::string> configFiles;
std::string selectedConfig;
std::string configDirectory;

void RefreshConfigList()
{
    configFiles.clear();
    for (const auto& entry : fs::directory_iterator(configDirectory))
    {
        if (entry.path().extension() == ".json")
        {
            configFiles.push_back(entry.path().filename().string());
        }
    }
}


void InitializeConfigSystem()
{
    char appDataPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appDataPath)))
    {
        configDirectory = std::string(appDataPath) + "\\Spectro";
        fs::create_directory(configDirectory);
        RefreshConfigList();
    }
}
