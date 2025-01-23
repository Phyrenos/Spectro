#include "../../Cheat.h"


void Cheat::Boxes(DirectX::SimpleMath::Vector2 pBase, float pWidth, float pTop,float pBottom,ImColor color) {
    switch (g.ESP_Box_Option) {
    case 0: // Box
        DrawOutlinedLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x + pWidth, pTop), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
        DrawOutlinedLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x - pWidth, pBottom), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
        DrawOutlinedLine(ImVec2(pBase.x + pWidth, pTop), ImVec2(pBase.x + pWidth, pBottom), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
        DrawOutlinedLine(ImVec2(pBase.x - pWidth, pBottom), ImVec2(pBase.x + pWidth, pBottom), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
        break;
    case 1:
        RectFilledOpacity(pBase.x - pWidth, pTop, pBase.x + pWidth, pBottom, ESP_Box_Filled, 0, 0, g.ESP_Box_Filled_Opacity);
        DrawOutlinedLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x + pWidth, pTop), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
        DrawOutlinedLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x - pWidth, pBottom), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
        DrawOutlinedLine(ImVec2(pBase.x + pWidth, pTop), ImVec2(pBase.x + pWidth, pBottom), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
        DrawOutlinedLine(ImVec2(pBase.x - pWidth, pBottom), ImVec2(pBase.x + pWidth, pBottom), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
        break;
    case 2:

        DrawLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x - pWidth + g.ESP_Corner_Length, pTop), color, 1.f); // Top-left corner
        DrawLine(ImVec2(pBase.x + pWidth - g.ESP_Corner_Length, pTop), ImVec2(pBase.x + pWidth, pTop), color, 1.f); // Top-right corner
        DrawLine(ImVec2(pBase.x - pWidth, pBottom), ImVec2(pBase.x - pWidth + g.ESP_Corner_Length, pBottom), color, 1.f); // Bottom-left corner
        DrawLine(ImVec2(pBase.x + pWidth - g.ESP_Corner_Length, pBottom), ImVec2(pBase.x + pWidth, pBottom), color, 1.f); // Bottom-right corner
        DrawLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x - pWidth, pTop + g.ESP_Corner_Length), color, 1.f); // Top-left vertical
        DrawLine(ImVec2(pBase.x + pWidth, pTop), ImVec2(pBase.x + pWidth, pTop + g.ESP_Corner_Length), color, 1.f); // Top-right vertical
        DrawLine(ImVec2(pBase.x - pWidth, pBottom - g.ESP_Corner_Length), ImVec2(pBase.x - pWidth, pBottom), color, 1.f); // Bottom-left vertical
        DrawLine(ImVec2(pBase.x + pWidth, pBottom - g.ESP_Corner_Length), ImVec2(pBase.x + pWidth, pBottom), color, 1.f); // Bottom-right vertical
        break;
    }
}