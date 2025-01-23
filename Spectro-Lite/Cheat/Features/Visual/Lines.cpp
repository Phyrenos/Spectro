#include "../../Cheat.h"


void Cheat::Tracers(DirectX::SimpleMath::Vector2 pBase, float pBottom) {
    switch (g.ESP_Line_Pos) {
    case 0: // Top of the screen
        DrawLine(ImVec2(g.GameRect.right / 2.f, g.GameRect.top), ImVec2(pBase.x, pBottom), ESP_Line, 1.f);
        break;
    case 1: // Middle of the screen
        DrawLine(ImVec2(g.GameRect.right / 2.f, g.GameRect.top + (g.GameRect.bottom - g.GameRect.top) / 2.f), ImVec2(pBase.x, pBottom), ESP_Line, 1.f);
        break;
    case 2: // Bottom of the screen
        DrawLine(ImVec2(g.GameRect.right / 2.f, g.GameRect.bottom), ImVec2(pBase.x, pBottom), ESP_Line, 1.f);
        break;
    }
}