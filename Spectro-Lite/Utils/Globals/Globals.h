#pragma once
#include <string>
#include <Windows.h>
#include "../../json.hpp"
#include "../../BezierCurve.h"
#include "../../Cheat/Arduino/Arduino.hpp"
struct Globals
{
    // System(Base
    bool Run = false;
    bool ShowMenu = false;
    bool AlwaysShow = true;
    CArduino* arduino;

  

    // GameData
    HWND GameHwnd = NULL;
    RECT GameRect{};
    POINT GamePoint{};
    std::string ProcName;
    std::unordered_map<int, std::string> PM{};

    // AimAssist
    bool AimAssist = false;
    float strength = 0.f;
    float RndStopPercent = 0.f;
    float AssistRandomness = 0.f;
    bool BezierEditor = false;
    float AA_AimFov = 100.f;
    bool AA_AimInOnly = false;
    bool AA_EnableSmoothing = false;
    bool AA_isvis = false;
    float AA_Smoothing = 0.1f;
    // AimBot
    bool AimBot = false;
    int AimbotMode = 0;
    
    float AimFov = 100.f;
    bool AimInOnly = false;
    bool EnableSmoothing = false;
    bool isvis = false;
    float Smoothing = 0.1f;
    int TargetMode = 0;
    BezierCurve aimCurve;
    int TargettedBone = 0;
    bool DEVMODULEVEC3TPOS = false;

    // Visual
    bool drawDead = false;
    bool drawNpc = false;
    bool ESP = true;
    bool ESP_Box = true;
    bool ESP_Box_Outline = true;
    float ESP_Box_Outline_Thickness = 1.f;
    float ESP_Box_Thickness = 1.f;
    int ESP_Box_Option = 0;
    bool ESP_Corner_Box = false;
    float ESP_Corner_Length = 15.5f;
    bool HEALTHGOD = false;
    int TargetPlayerID = 0;
    bool ESP_Box_Filled = false;
    float ESP_Box_Filled_Opacity = 0.0f;
    bool ESP_Line = false;
    int ESP_Line_Pos = 0;
    bool ESP_Name = true;
    bool ESP_Weapon_Names = true;
    bool ESP_Distance = true;
    bool ESP_HealthBar = false;
    bool ESP_ArmorBar = false;
    bool ESP_Skeleton = true;
    bool ESP_SK_Outline = true;
    float ESP_Skeleton_thickness = 1.f;
    float ESP_Skeleton_Outline_thickness = 1.f;
    float ESP_MaxDistance = 1000.f;

    // Misc
    /*bool GodMode = false;
    bool NoRecoil = false;
    bool WeaponDamageModifier = false;
    float weaponDamageAmount = 0.f;
    float recoilAmount = 0.f;
    bool NoSpread = false;
    float spreadAmount = 0.f;
    bool RangeBypass = false;
    bool FastReload = false;
    float ReloadSpeed = 0;*/
    // System(Cheat
    bool Crosshair = false;
    bool StreamProof = false;
    bool WaterMark = true;

    // Key
    int MenuKey = VK_INSERT;
    int AimKey0 = VK_RBUTTON;
    int AimKey1 = VK_LBUTTON;

};

extern Globals g;
extern bool IsKeyDown(int VK);
extern const char* KeyNames[];
extern nlohmann::json to_json();
extern void from_json(const nlohmann::json& j);
extern void save_to_file(const std::string& filepath);
extern void load_from_file(const std::string& filepath);