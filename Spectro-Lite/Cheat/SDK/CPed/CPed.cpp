#include "CPed.h"

bool CPed::get_player(uintptr_t& base)
{
    ptr = base;
    return ptr == NULL ? false : true;
}

uintptr_t CPed::get_weapon()
{
    uintptr_t weapon_mgr = m.SysRead<uintptr_t>(ptr + offset::m_pWeaponManager);

    return m.SysRead<uintptr_t>(weapon_mgr + 0x20);
}

bool CPed::isPlayer()
{
    return player_info != NULL;
}

bool CPed::isDead()
{
    return m_fHealth <= 0 || m_pVecPosition == Vector3(0.f, 0.f, 0.f);
}

bool CPed::Update()
{
    player_info = m.SysRead<uintptr_t>(ptr + offset::m_pInfo);
    current_weapon = get_weapon();
    m_fID = m.SysRead<int>(player_info + 0xE8);
    m_fHealth = m.SysRead<float>(ptr + offset::m_pHealth);
    m_fMaxHealth = m.SysRead<float>(ptr + offset::m_pMaxHealth);
    m_fArmor = m.SysRead<float>(ptr + offset::m_pArmor);
    m_pVecPosition = m.SysRead<Vector3>(ptr + offset::m_pLocation);

    if (isDead())
        return false;

    m_pBoneMatrix = m.SysRead<Matrix>(ptr + offset::m_bMatrix);
    UpdateBones();

    return true;
}

void CPed::UpdateBones()
{
    CBone bone = m.SysRead<CBone>(ptr + offset::m_pBoneList);
    BoneList[HEAD] = Vec3_Transform(&bone.gHead, &m_pBoneMatrix);
    BoneList[LEFTFOOT] = Vec3_Transform(&bone.gLeftFoot, &m_pBoneMatrix);
    BoneList[RIGHTFOOT] = Vec3_Transform(&bone.gRightFoot, &m_pBoneMatrix);
    BoneList[LEFTANKLE] = Vec3_Transform(&bone.gLeftAnkle, &m_pBoneMatrix);
    BoneList[RIGHTANKLE] = Vec3_Transform(&bone.gRightAnkle, &m_pBoneMatrix);
    BoneList[LEFTHAND] = Vec3_Transform(&bone.gLeftHand, &m_pBoneMatrix);
    BoneList[RIGHTHAND] = Vec3_Transform(&bone.gRightHand, &m_pBoneMatrix);
    BoneList[NECK] = Vec3_Transform(&bone.gNeck, &m_pBoneMatrix);
    BoneList[HIP] = Vec3_Transform(&bone.gHip, &m_pBoneMatrix);
}


float CPed::GetPlayerHealth()
{

    return m.SysRead<float>(ptr + offset::m_pHealth);
}

float CPed::GetPlayerMaxHealth()
{

    return m.SysRead<float>(ptr + offset::m_pMaxHealth);
}

//void CPed::SetPlayerHealth(float Health)
//{
//    m.SysWrite<float>(ptr + offset::m_pHealth, Health);
//}


float CPed::GetPlayerArmor() {
    return m.SysRead<float>(ptr + offset::m_pArmor);
}

//void CPed::SetPlayerArmor(float Armor) {
//    m.SysWrite<float>(ptr + offset::m_pArmor, Armor);
//}