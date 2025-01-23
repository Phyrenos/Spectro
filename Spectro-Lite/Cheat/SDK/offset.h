#pragma once

/*
// b2944
namespace offset
{
    // Base
    constexpr auto GameWorld = 0x257BEA0;
    constexpr auto ReplayInterface = 0x1F42068;
    constexpr auto ViewPort = 0x1FEAAC0;
    constexpr auto Camera = 0x1FEB698;

    // Ped
    constexpr auto m_pBoneMatrix = 0x60;
    constexpr auto m_pLocation = 0x90;
    constexpr auto m_pGodMode = 0x189;
    constexpr auto m_pHealth = 0x280;
    constexpr auto m_pMaxHealth = 0x284;
    constexpr auto m_pBoneList = 0x410;
    constexpr auto m_pArmor = 0x150C;
   
    // Pointer
    constexpr auto m_pInfo = 0x10A8;          // PlayerInfo
    constexpr auto m_pWeaponManager = 0x10B8; // WeaponManager

    // CurrentWeapon (WepaonManager + 0x20)
    constexpr auto m_WepSpread = 0x74;
    constexpr auto m_WepRecoil = 0x2F4;
    constexpr auto m_WepRange  = 0x28C;
}
*/

// b3095
namespace offset
{
    // Base
    constexpr auto GameWorld = 0x2593320;
    constexpr auto ReplayInterface = 0x1F58B58;
    constexpr auto ViewPort = 0x20019E0;
    constexpr auto Camera = 0x20025B8;
    constexpr auto PlayerInterface = 0x1e47938;
    constexpr auto Waypoint = 0x2002fa0;
    constexpr auto W2S = 0xa4aae0;
    
    // Most Player
    constexpr auto bIsPlayerAiming = 0x2D3839C;
    constexpr auto PlayerAimingAt = 0x200FA10;
    constexpr auto HandleBullet = 0x100F5A4;
    constexpr auto BlipList = 0x2002FA0;

    // Ped
    constexpr auto m_bMatrix = 0x60;
    constexpr auto m_pLocation = 0x90;
    constexpr auto m_pHealth = 0x280;
    constexpr auto m_pMaxHealth = 0x284;
    constexpr auto m_pBoneList = 0x410;
    constexpr auto m_pArmor = 0x150C;
   // constexpr auto IDtoName = 0x254f8;// 34d20 0x254f8

    constexpr auto EntityType = 0x1098;
    constexpr auto FragInsNmGTA = 0x1430;
    constexpr auto ConfigFlags = 0x1444;
    constexpr auto LastVehicle = 0xD10;
    constexpr auto Driver = 0xC90;
    constexpr auto DoorLock = 0x13C0;
    constexpr auto Stamina = 0xCF4;
    constexpr auto VisibleFlag = 0x145C;

    // Pointer
    constexpr auto m_pInfo = 0x10A8;          // PlayerInfo
    constexpr auto m_pWeaponManager = 0x10B8; // WeaponManager
    
    // CurrentWeapon (WepaonManager + 0x20)
    constexpr auto m_WepReload = 0x134;
    constexpr auto m_WepSpread = 0x74; // 0x84
    constexpr auto m_WepRecoil = 0x2F4;
    constexpr auto m_WepRange = 0x28C;
}

