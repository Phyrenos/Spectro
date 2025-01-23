#include "Cheat.h"
#include "..\Overlay\Overlay.h"
#include "../ext/Strings/xor.h"
#include "../ConfigManager.h"
#include "../ext/Curl/curl.h"
#include <filesystem>

void Cheat::RenderInfo()
{
    if (g.WaterMark) {
        std::string text = "Spectro | " + std::to_string((int)ImGui::GetIO().Framerate) + "FPS";
        String(ImVec2(8.f, 8.f), ImColor(1.f, 1.f, 1.f, 1.f), text.c_str());
    }

    if (g.Crosshair)
    {
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2((float)g.GameRect.right / 2.f, (float)g.GameRect.bottom / 2.f), 3, ImColor(0.f, 0.f, 0.f, 1.f));
        ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2((float)g.GameRect.right / 2.f, (float)g.GameRect.bottom / 2.f), 2, ImColor(1.f, 1.f, 1.f, 1.f));
    }

    // AimFov
    if (g.AimBot)
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(g.GameRect.right / 2.f, g.GameRect.bottom / 2.f), g.AimFov, ImColor(1.f, 1.f, 1.f, 1.f));
    if (g.AimAssist)
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(g.GameRect.right / 2.f, g.GameRect.bottom / 2.f), g.AA_AimFov, ImColor(1.f, 1.f, 1.f, 1.f));
}

int i = 0;


void Cheat::RenderESP()
{
    CPed* pLocal = &local;
    Matrix ViewMatrix = m.SysRead<Matrix>(ViewPort + 0x24C);

    if (!pLocal->Update())
        return;

    for (auto& ped : EntityList)
    {
        CPed* pEntity = &ped;

        if (!pEntity->Update())
            continue;

        float pDistance = GetDistance(pEntity->m_pVecPosition, pLocal->m_pVecPosition);

        if (pDistance >= g.ESP_MaxDistance)
            continue;

        if (!pEntity->isPlayer() && !g.drawNpc)
            continue;
        if (pEntity->isDead() && !g.drawDead)
            continue;

        // Box
        Vector2 pBase{}, pHead{}, pNeck{}, pLeftFoot{}, pRightFoot{};
        if (!WorldToScreen(ViewMatrix, pEntity->m_pVecPosition, pBase) || !WorldToScreen(ViewMatrix, pEntity->BoneList[HEAD], pHead) || !WorldToScreen(ViewMatrix, pEntity->BoneList[NECK], pNeck) || !WorldToScreen(ViewMatrix, pEntity->BoneList[LEFTFOOT], pLeftFoot) || !WorldToScreen(ViewMatrix, pEntity->BoneList[RIGHTFOOT], pRightFoot))
            continue;

        float HeadToNeck = pNeck.y - pHead.y;
        float pTop = pHead.y - (HeadToNeck * 2.5f);
        float pBottom = (pLeftFoot.y > pRightFoot.y ? pLeftFoot.y : pRightFoot.y) * 1.001f;
        float pHeight = pBottom - pTop;
        float pWidth = pHeight / 3.5f;
        float bScale = pWidth / 1.5f;
       
        ImColor color = pEntity->isPlayer() ? ESP_Player : ESP_NPC;

        if (g.ESP_Line) {
            Tracers(pBase, pBottom);
        }

        // Box

        if (g.ESP_Box) {
            Boxes(pBase, pWidth, pTop, pBottom, color);
        }


        if (g.ESP_Name) {
            Names(pEntity, pBottom, pBase);
        }

        if (g.ESP_Skeleton) {
            Skeleton(pEntity, ViewMatrix);
        }

        // Healthbar
        if (g.ESP_HealthBar)
        {
            HealthBar((pBase.x - pWidth) - 4.f, pBottom, 2.f, -pHeight, pEntity->m_fHealth, pEntity->m_fMaxHealth);
        }

        if (g.ESP_ArmorBar) {
            if (pEntity->m_fArmor > 0.f)
                ArmorBar((pBase.x + pWidth) + 3.f, pBottom, 2.f, -pHeight, pEntity->m_fArmor, 100);
        }

        // Distance
        if (g.ESP_Distance)
        {
            std::string dist = std::to_string((int)pDistance) + "m";
            String(ImVec2(pBase.x - ImGui::CalcTextSize(dist.c_str()).x / 2.f, pBottom), ImColor(1.f, 1.f, 1.f, 1.f), dist.c_str());
        }
    }
}

void Cheat::DrawBezierEditor(BezierCurve& curve)
{
    ImGui::Begin("##DrawBezierEditor", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text("Bezier Curve Editor");
    ImGui::Separator();

    // Adjust control points with sliders
    ImGui::SliderFloat2("P0", &curve.p0.x, 0.0f, 1.0f);
    ImGui::SliderFloat2("P1", &curve.p1.x, 0.0f, 1.0f);
    ImGui::SliderFloat2("P2", &curve.p2.x, 0.0f, 1.0f);
    ImGui::SliderFloat2("P3", &curve.p3.x, 0.0f, 1.0f);

    const ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
    const ImVec2 canvas_size = ImVec2(700, 400);
    const ImVec2 canvas_end = ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y);

    ImGui::Dummy(canvas_size); 

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRect(canvas_pos, canvas_end, IM_COL32(255, 255, 255, 255));

    ImVec2 control_points[] = {
        ImVec2(canvas_pos.x + curve.p0.x * canvas_size.x, canvas_pos.y + (1.0f - curve.p0.y) * canvas_size.y),
        ImVec2(canvas_pos.x + curve.p1.x * canvas_size.x, canvas_pos.y + (1.0f - curve.p1.y) * canvas_size.y),
        ImVec2(canvas_pos.x + curve.p2.x * canvas_size.x, canvas_pos.y + (1.0f - curve.p2.y) * canvas_size.y),
        ImVec2(canvas_pos.x + curve.p3.x * canvas_size.x, canvas_pos.y + (1.0f - curve.p3.y) * canvas_size.y)
    };

    draw_list->AddBezierCubic(
        control_points[0], control_points[1], control_points[2], control_points[3],
        IM_COL32(255, 0, 0, 255), 2.0f);

    draw_list->AddLine(control_points[0], control_points[1], IM_COL32(255, 255, 0, 255), 1.0f);
    draw_list->AddLine(control_points[2], control_points[3], IM_COL32(255, 255, 0, 255), 1.0f);

    for (int i = 0; i < 4; ++i)
    {
        draw_list->AddCircleFilled(control_points[i], 5.0f, IM_COL32(0, 255, 0, 255));
    }
    ImGui::End();
}
