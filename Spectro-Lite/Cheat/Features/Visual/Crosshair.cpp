//#include "../../Cheat.h"


//void Cheat::Boxes(DirectX::SimpleMath::Vector2 pBase, float pWidth, float pTop, float pBottom, ImColor color) {
//    switch (g.ESP_Box_Option) {
//    case 0: // Box
//        DrawOutlinedLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x + pWidth, pTop), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
//        DrawOutlinedLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x - pWidth, pBottom), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
//        DrawOutlinedLine(ImVec2(pBase.x + pWidth, pTop), ImVec2(pBase.x + pWidth, pBottom), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
//        DrawOutlinedLine(ImVec2(pBase.x - pWidth, pBottom), ImVec2(pBase.x + pWidth, pBottom), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
//        break;
//    case 1: // dot Crosshair
//        RectFilledOpacity(pBase.x - pWidth, pTop, pBase.x + pWidth, pBottom, ESP_Box_Filled, 0, 0, g.ESP_Box_Filled_Opacity);
//        DrawOutlinedLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x + pWidth, pTop), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
//        DrawOutlinedLine(ImVec2(pBase.x - pWidth, pTop), ImVec2(pBase.x - pWidth, pBottom), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
//        DrawOutlinedLine(ImVec2(pBase.x + pWidth, pTop), ImVec2(pBase.x + pWidth, pBottom), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
//        DrawOutlinedLine(ImVec2(pBase.x - pWidth, pBottom), ImVec2(pBase.x + pWidth, pBottom), color, ESP_Player_outline, g.ESP_Box_Thickness, g.ESP_Box_Outline_Thickness, g.ESP_Box_Outline);
//        break;
//    case 2: // + Crosshair
//
//        break;
//    }
//}