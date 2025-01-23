#include "../../Cheat.h"


void Cheat::Skeleton(CPed* pEntity, DirectX::SimpleMath::Matrix ViewMatrix) {
    for (int j = 0; j < 5; j++)
    {
        Vector3 skList[][2] = { { pEntity->BoneList[NECK], pEntity->BoneList[HIP] }, { pEntity->BoneList[NECK], pEntity->BoneList[LEFTHAND] },
            { pEntity->BoneList[NECK], pEntity->BoneList[RIGHTHAND] }, { pEntity->BoneList[HIP], pEntity->BoneList[LEFTFOOT] }, { pEntity->BoneList[HIP], pEntity->BoneList[RIGHTFOOT] } };

        Vector2 ScreenB1{}, ScreenB2{};
        if (Vec3_Empty(skList[j][0]) || Vec3_Empty(skList[j][1]))
            break;
        else if (!WorldToScreen(ViewMatrix, skList[j][0], ScreenB1) || !WorldToScreen(ViewMatrix, skList[j][1], ScreenB2))
            break;
        DrawOutlinedLine(ImVec2(ScreenB1.x, ScreenB1.y), ImVec2(ScreenB2.x, ScreenB2.y), ESP_Skeleton, ESP_Skeleton_outline, g.ESP_Skeleton_thickness, g.ESP_Skeleton_Outline_thickness, g.ESP_SK_Outline);
        //DrawLine(ImVec2(ScreenB1.x, ScreenB1.y), ImVec2(ScreenB2.x, ScreenB2.y), ESP_Skeleton, g.ESP_Skeleton_thickness);
    }
}