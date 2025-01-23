#pragma once
#include <string>
#include <vector>

void InitializeConfigSystem();
void RefreshConfigList();

extern std::vector<std::string> configFiles;
extern std::string selectedConfig;
extern std::string configDirectory;