#include "Globals.h"
#include "../../Cheat/Cheat.h"
#include <fstream>
Globals g;

bool IsKeyDown(int VK)
{
    return (GetAsyncKeyState(VK) & 0x8000) != 0;
}

nlohmann::json to_json()
{
    return {
        {"AimBot", g.AimBot},
        {"AimbotMode", g.AimbotMode},
        {"AimFov", g.AimFov},
        {"AimInOnly", g.AimInOnly},
        {"EnableSmoothing", g.EnableSmoothing},
        {"isvis", g.isvis},
        {"Smoothing", g.Smoothing},
        {"TargetMode", g.TargetMode},
        {"TargettedBone", g.TargettedBone},
        {"drawDead", g.drawDead},
        {"drawNpc", g.drawNpc},
        {"ESP", g.ESP},
        {"ESP_Box", g.ESP_Box},
        {"ESP_Box_Outline", g.ESP_Box_Outline},
        {"ESP_Box_Outline_Thickness", g.ESP_Box_Outline_Thickness},
        {"ESP_Box_Thickness", g.ESP_Box_Thickness},
        {"ESP_Box_Option", g.ESP_Box_Option},
        {"ESP_Corner_Box", g.ESP_Corner_Box},
        {"ESP_Corner_Length", g.ESP_Corner_Length},
        {"ESP_Box_Filled", g.ESP_Box_Filled},
        {"ESP_Box_Filled_Opacity", g.ESP_Box_Filled_Opacity},
        {"ESP_Line", g.ESP_Line},
        {"ESP_Line_Pos", g.ESP_Line_Pos},
        {"ESP_Name", g.ESP_Name},
        {"ESP_Weapon_Names", g.ESP_Weapon_Names},
        {"ESP_Distance", g.ESP_Distance},
        {"ESP_HealthBar", g.ESP_HealthBar},
        {"ESP_Skeleton", g.ESP_Skeleton},
        {"ESP_SK_Outline", g.ESP_SK_Outline},
        {"ESP_Skeleton_thickness", g.ESP_Skeleton_thickness},
        {"ESP_Skeleton_Outline_thickness", g.ESP_Skeleton_Outline_thickness},
        {"ESP_MaxDistance", g.ESP_MaxDistance},
        /*{"GodMode", g.GodMode},
        {"NoRecoil", g.NoRecoil},
        {"recoilAmount", g.recoilAmount},
        {"NoSpread", g.NoSpread},
        {"spreadAmount", g.spreadAmount},
        {"RangeBypass", g.RangeBypass},
        {"FastReload", g.FastReload},
        {"ReloadSpeed", g.ReloadSpeed},*/
        {"Crosshair", g.Crosshair},
        {"StreamProof", g.StreamProof},
        {"WaterMark", g.WaterMark},
        {"MenuKey", g.MenuKey},
        {"AimKey0", g.AimKey0},
        {"AimKey1", g.AimKey1}


    };
}


void from_json(const nlohmann::json& j)
{
    j.at("AimBot").get_to(g.AimBot);
    j.at("AimbotMode").get_to(g.AimbotMode);
    j.at("AimFov").get_to(g.AimFov);
    j.at("AimInOnly").get_to(g.AimInOnly);
    j.at("EnableSmoothing").get_to(g.EnableSmoothing);
    j.at("isvis").get_to(g.isvis);
    j.at("Smoothing").get_to(g.Smoothing);
    j.at("TargetMode").get_to(g.TargetMode);
    j.at("TargettedBone").get_to(g.TargettedBone);
    j.at("drawDead").get_to(g.drawDead);
    j.at("drawNpc").get_to(g.drawNpc);
    j.at("ESP").get_to(g.ESP);
    j.at("ESP_Box").get_to(g.ESP_Box);
    j.at("ESP_Box_Outline").get_to(g.ESP_Box_Outline);
    j.at("ESP_Box_Outline_Thickness").get_to(g.ESP_Box_Outline_Thickness);
    j.at("ESP_Box_Thickness").get_to(g.ESP_Box_Thickness);
    j.at("ESP_Box_Option").get_to(g.ESP_Box_Option);
    j.at("ESP_Corner_Box").get_to(g.ESP_Corner_Box);
    j.at("ESP_Corner_Length").get_to(g.ESP_Corner_Length);
    j.at("ESP_Box_Filled").get_to(g.ESP_Box_Filled);
    j.at("ESP_Box_Filled_Opacity").get_to(g.ESP_Box_Filled_Opacity);
    j.at("ESP_Line").get_to(g.ESP_Line);
    j.at("ESP_Line_Pos").get_to(g.ESP_Line_Pos);
    j.at("ESP_Name").get_to(g.ESP_Name);
    j.at("ESP_Weapon_Names").get_to(g.ESP_Weapon_Names);
    j.at("ESP_Distance").get_to(g.ESP_Distance);
    j.at("ESP_HealthBar").get_to(g.ESP_HealthBar);
    j.at("ESP_Skeleton").get_to(g.ESP_Skeleton);
    j.at("ESP_SK_Outline").get_to(g.ESP_SK_Outline);
    j.at("ESP_Skeleton_thickness").get_to(g.ESP_Skeleton_thickness);
    j.at("ESP_Skeleton_Outline_thickness").get_to(g.ESP_Skeleton_Outline_thickness);
    j.at("ESP_MaxDistance").get_to(g.ESP_MaxDistance);
    /*j.at("GodMode").get_to(g.GodMode);
    j.at("NoRecoil").get_to(g.NoRecoil);
    j.at("recoilAmount").get_to(g.recoilAmount);
    j.at("NoSpread").get_to(g.NoSpread);
    j.at("spreadAmount").get_to(g.spreadAmount);
    j.at("RangeBypass").get_to(g.RangeBypass);
    j.at("FastReload").get_to(g.FastReload);
    j.at("ReloadSpeed").get_to(g.ReloadSpeed);*/
    j.at("Crosshair").get_to(g.Crosshair);
    j.at("StreamProof").get_to(g.StreamProof);
    j.at("WaterMark").get_to(g.WaterMark);
    j.at("MenuKey").get_to(g.MenuKey);
    j.at("AimKey0").get_to(g.AimKey0);
    j.at("AimKey1").get_to(g.AimKey1);
}

void save_to_file(const std::string& filepath)
{
    std::ofstream file(filepath);
    if (file.is_open())
    {
        file << to_json().dump(4);
        file.close();
    }
}


void load_from_file(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (file.is_open())
    {
        nlohmann::json j;
        file >> j;
        from_json(j);
        file.close();
    }
}



const char* KeyNames[] =
{
    "NONE",
    "Mouse Left",
    "Mouse Right",
    "Cancel",
    "Middle Center",
    "MouseSide1",
    "MouseSide2",
    "",
    "Backspace",
    "Tab",
    "",
    "",
    "Clear",
    "Enter",
    "",
    "",
    "Shift",
    "Ctrl",
    "Alt",
    "Pause",
    "CapsLock",
    "",
    "",
    "",
    "",
    "",
    "",
    "Escape",
    "",
    "",
    "",
    "",
    "Space",
    "Page Up",
    "Page Down",
    "End",
    "Home",
    "Left",
    "Up",
    "Right",
    "Down",
    "",
    "",
    "",
    "Print",
    "Insert",
    "Delete",
    "",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "",
    "",
    "",
    "",
    "",
    "Numpad 0",
    "Numpad 1",
    "Numpad 2",
    "Numpad 3",
    "Numpad 4",
    "Numpad 5",
    "Numpad 6",
    "Numpad 7",
    "Numpad 8",
    "Numpad 9",
    "Multiply",
    "Add",
    "",
    "Subtract",
    "Decimal",
    "Divide",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
};