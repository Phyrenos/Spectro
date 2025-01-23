#pragma once
#include "../../../Utils/Memory/Memory.h"
#include "../Game/GameSDK.h"
#include "../offset.h"

class CPed
{
public:
    uintptr_t ptr;
    uintptr_t player_info;
    uintptr_t current_weapon;

    uint64_t crSkeletonData;
    int m_fID;
    float m_fArmor;
    float m_fHealth;
    float m_fMaxHealth;
    float m_fStamina;
    Vector3 m_pVecPosition;
    Matrix m_pBoneMatrix;
    Vector3 BoneList[9]{};
    std::unordered_map<unsigned int, unsigned> MaskToBoneId;
    bool get_player(uintptr_t& address);

    uintptr_t get_weapon();

    bool isPlayer();
    bool isDead();

    bool Update();
    void UpdateBones();

    float GetPlayerHealth();
    float GetPlayerMaxHealth();
    void SetPlayerHealth(float value);

    float GetPlayerArmor();

    void SetPlayerArmor(float Armor);

};

