#pragma once
#include "../../../Utils/Globals/Globals.h"
#include "../../../Utils/SimpleMath/SimpleMath.h"
using namespace DirectX::SimpleMath;

extern struct CBone
{
    Vector3 gHead;      // 0
    char ped_0[0x4]{};
    Vector3 gLeftFoot;  // 1
    char ped_1[0x4]{};
    Vector3 gRightFoot; // 2
    char ped_2[0x4]{};
    Vector3 gLeftAnkle; // 3
    char ped_3[0x4]{};
    Vector3 gRightAnkle;// 4
    char ped_4[0x4]{};
    Vector3 gLeftHand;  // 5
    char ped_5[0x4]{};
    Vector3 gRightHand; // 6
    char ped_6[0x4]{};
    Vector3 gNeck;      // 7
    char ped_7[0x4]{};
    Vector3 gHip;       // 8
};

enum Bone : int
{
    HEAD,
    LEFTFOOT,
    RIGHTFOOT,
    LEFTANKLE,
    RIGHTANKLE,
    LEFTHAND,
    RIGHTHAND,
    NECK,
    HIP
};

extern bool Vec3_Empty(const Vector3& value);
extern Vector3 Vec3_Transform(Vector3* vIn, Matrix* mIn);
extern void NormalizeAngles(Vector3& angle);
extern Vector3 CalcAngle(Vector3 local_cam, Vector3 to_point);
extern float GetDistance(Vector3 value1, Vector3 value2);
extern bool WorldToScreen(const Matrix& ViewMatrix, const Vector3& vWorld, Vector2& vOut);