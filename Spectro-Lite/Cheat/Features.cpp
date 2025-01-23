#include "Cheat.h"

#include <Windows.h>
#include <random>

float RandomFloat(float min, float max) 
{
    static std::random_device rd; 
    static std::mt19937 gen(rd()); 
    std::uniform_real_distribution<float> dist(min, max); 
    return dist(gen);
}

void MoveToPos(Vector2 pos)
{
    char dataX = static_cast<char>(pos.x);
    char dataY = static_cast<char>(pos.y);
    g.arduino->SendCmd({ 0x01, dataX, dataY }); // 0x01 for Move command
}


void Cheat::Misc()
{
    while (g.Run)
    {

      /*  if (g.HEALTHGOD) {
            if (m.SysRead<float>(local.ptr + offset::m_pHealth) < m.SysRead<float>(local.ptr + offset::m_pMaxHealth) - 3.0) {
                m.SysWrite<float>(local.ptr + offset::m_pHealth, m.SysRead<float>(local.ptr + offset::m_pMaxHealth) - 3.0);
            }
            
           

        }*/

        
        
        /*if (g.NoRecoil) 
            m.Write<float>(local.current_weapon + offset::m_WepRecoil, g.recoilAmount);   
        if (g.NoSpread)
            m.Write<float>(local.current_weapon + offset::m_WepSpread, g.spreadAmount);
        if (g.RangeBypass)
            m.Write<float>(local.current_weapon + offset::m_WepRange, 999.f);
        if (g.FastReload)
            m.Write<float>(local.current_weapon + offset::m_WepReload, g.ReloadSpeed);*/
        Sleep(100);
    }
}

void Cheat::UpdateList()
{
    while (g.Run)
    {
        std::vector<CPed> list;
       // std::cout << m.BaseAddress << std::endl;

        GWorld = m.SysRead<uintptr_t>(m.BaseAddress + offset::GameWorld);
        //std::cout << GWorld << std::endl;
        local.ptr = m.SysRead<uintptr_t>(GWorld + 0x8);
        ViewPort = m.SysRead<uintptr_t>(m.BaseAddress + offset::ViewPort);
        // Access EntityList
        uintptr_t ReplayInterface = m.SysRead<uintptr_t>(m.BaseAddress + offset::ReplayInterface);
        uintptr_t EntityListPtr = m.SysRead<uintptr_t>(ReplayInterface + 0x18);
        uintptr_t EntityList = m.SysRead<uintptr_t>(EntityListPtr + 0x100);
        std::cout << EntityList << std::endl;
        for (int i = 0; i < 256; i++)
        {
            CPed ped = CPed{};
            uintptr_t player = m.SysRead<uintptr_t>(EntityList + (i * 0x10));
            
            if (player == local.ptr)
                continue;
            else if (!ped.get_player(player))
                continue;
            else if (!ped.Update())
                continue;

            list.push_back(ped);
        }

        this->EntityList = list;
        Sleep(500);
    }
}

bool Cheat::IsVisible(CPed* Target) {
    BYTE VisCheck = m.SysRead<BYTE>(Target->ptr + 0x145C);
    if (g.isvis) {
        if (VisCheck == 36 || VisCheck == 0 || VisCheck == 4)
            return false;
    }
    
    return true;
}

CPed Cheat::FindBestTarget()
{
    CPed target{};
    CPed* pLocal = &local;
    Matrix ViewMatrix = m.SysRead<Matrix>(ViewPort + 0x24C);


    Vector2 Center = Vector2(g.GameRect.right / 2.f, g.GameRect.bottom / 2.f);

    float lowestHealth = FLT_MAX;
    float closestDistance = FLT_MAX; // Variable for closest ped distance

    for (auto& ped : EntityList)
    {
        CPed* pEntity = &ped;

        // Checks
        if (!pLocal->Update())
            break;
        else if (!pEntity->Update())
            continue;

        Vector2 pScreen{};
        if (!WorldToScreen(ViewMatrix, pEntity->BoneList[g.TargettedBone], pScreen))
            continue;

        float dis = GetDistance(pEntity->m_pVecPosition, pLocal->m_pVecPosition);
        switch (g.TargetMode) {
        case 0: // FOV-based targeting
        {
            float FOV = abs((Center - pScreen).Length());

            if (FOV < g.AimFov && dis < closestDistance && IsVisible(pEntity)) {
                closestDistance = dis;
                target = ped;
            }
            break;
        }
        case 1: // Health-based targeting
        {
            float entityHealth = pEntity->m_fHealth;
            if (entityHealth > 0 && entityHealth < lowestHealth && dis < closestDistance && IsVisible(pEntity)) {
                closestDistance = dis;
                lowestHealth = entityHealth;
                target = ped;
            }
            break;
        }
        }
    }

    return target;

}