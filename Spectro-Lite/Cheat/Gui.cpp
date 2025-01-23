#include "Cheat.h"
#include "..\Overlay\Overlay.h"
#include "../ext/Strings/xor.h"
#include "../ConfigManager.h"


namespace fs = std::filesystem;
std::vector<std::string> MenuTitleList = { "AimBot", "Visual", "Misc", "Config" };
std::vector<std::string> VisualTitleList = { "ESP", "Color", "Builder" };
std::vector<std::string> MiscTitleList = { "Weapons", "Player", "Vehicles" };



static void CreateModernStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    // Some overall scaling to ensure the style is more comfortable on high DPI displays.
    style.ScaleAllSizes(1.0f);

    // Window
    style.WindowPadding = ImVec2(10, 10);
    style.WindowRounding = 12.0f;  // Rounded corners
    style.WindowBorderSize = 1.5f;   // Thicker border
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

    // Frame (generic widgets like checkboxes, sliders, etc.)
    style.FramePadding = ImVec2(8, 4);
    style.FrameRounding = 6.0f;
    style.FrameBorderSize = 1.0f;

    // Popups
    style.PopupRounding = 8.f;
    style.PopupBorderSize = 1.f;

    // Columns
    style.CellPadding = ImVec2(5, 5);

    // Grab (sliders, scrollbars)
    style.GrabRounding = 4.0f;
    style.GrabMinSize = 15.0f;

    // Tabs
    style.TabRounding = 6.0f;
    style.TabBorderSize = 1.0f;
    style.TouchExtraPadding = ImVec2(5.f, 5.f);

    // Colors: We'll override them in a fresh palette
    ImVec4* colors = style.Colors;

    // A base "dark purple + dark grey" palette. 
    // Tweak them as you like. This is just an example.
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.13f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.35f, 0.55f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.22f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.22f, 0.33f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.26f, 0.36f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.11f, 0.10f, 0.18f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 0.18f, 0.38f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.05f, 0.08f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.15f, 0.20f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.11f, 0.11f, 0.15f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.43f, 0.55f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.35f, 0.35f, 0.50f, 0.65f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.40f, 0.40f, 0.60f, 0.75f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.74f, 0.64f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.54f, 0.44f, 0.90f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.54f, 0.95f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.28f, 0.22f, 0.48f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.28f, 0.60f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.44f, 0.36f, 0.72f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.30f, 0.22f, 0.45f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.40f, 0.28f, 0.55f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.45f, 0.35f, 0.65f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.30f, 0.30f, 0.40f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.45f, 0.45f, 0.60f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.50f, 0.50f, 0.70f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.40f, 0.35f, 0.50f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.50f, 0.45f, 0.60f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.60f, 0.55f, 0.70f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.24f, 0.18f, 0.35f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.34f, 0.26f, 0.46f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.40f, 0.30f, 0.55f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.10f, 0.20f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.28f, 0.20f, 0.40f, 1.00f);


    // Text
    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.55f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.46f, 0.32f, 0.66f, 0.50f);

    // We can keep on adjusting as we like...
}


void Cheat::RenderMenuV2() {
    CreateModernStyle();
    static int index = 0;
    ImGui::SetNextWindowSize(ImVec2(719.f, 75.f));
    ImGui::Begin(_("Spectro [Slotted] [Developer]"), &g.AlwaysShow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);

    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    float centerX = (displaySize.x - windowSize.x) * 0.5f;
    ImGui::SetWindowPos(ImVec2(centerX, 0.0f));

    float iconPadding = 20.0f;
    ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x - 560.f); 
    ImGui::SetCursorPosY(25.0f);
    for (int i = 0; i < MenuTitleList.size(); i++)
    {
        static float width = (ImGui::GetContentRegionAvail().x / 5.f) - 2.f;
        if (ImGui::Button(MenuTitleList[i].c_str(), ImVec2(width, 25.f)))
            index = i;


        if (i != MenuTitleList.size() - 1)
            ImGui::SameLine();

    }
    ImGui::SameLine();

    ImGui::PushFont(TopBarTitle);
    const char* text = _("Spectro");
    ImVec2 textSize = ImGui::CalcTextSize(text);
    float posX = 25.0f; // Margin from the left // float posX = windowSize.x - textSize.x - 10.0f; // 10.0f is a margin from the right
    float posY = (windowSize.y - textSize.y) * 0.5f;
    ImGui::SetCursorPos(ImVec2(posX, posY));
    ImGui::Text(_("%s"), text);
    ImGui::PopFont();




    switch (index) {
    case 0: // Aimbot
    {
        ImGui::Begin("##MainWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowSize(ImVec2(700, 350));
        ImGui::Columns(2, nullptr, false);
        // First column - Boxes
        ImGui::BeginChild("##Aimbot", ImVec2(0, 150), true, ImGuiWindowFlags_NoScrollbar);
        // Center text horizontally


        ImVec2 BoxeschildSize = ImGui::GetWindowSize();
        const char* Boxestext = "Aimbot";
        ImVec2 BoxestextSize = ImGui::CalcTextSize(text);
        float BoxestextX = (BoxeschildSize.x - BoxestextSize.x) / 2.0f; // Center X
        float BoxestextY = 10.0f; // Padding from the top

        // Position the text
        ImGui::SetCursorPos(ImVec2(BoxestextX, BoxestextY));
        ImGui::Text("%s", Boxestext);

        ImGui::Separator();
        ImGui::Checkbox(_("Aimbot"), &g.AimBot);
        if (g.AimBot)
        {
            ImGui::SliderFloat("Fov", &g.AimFov, 0.0f, 1000.0f, "%.0f R");
            ImGui::Checkbox("Right Click Only", &g.AimInOnly);
            ImGui::Checkbox("Smoothing", &g.EnableSmoothing);
            if (g.EnableSmoothing)
            {
                ImGui::SliderFloat("Smoothing", &g.Smoothing, 0.1f, 1.0f, "%0.1f");
            }
            ImGui::Checkbox("Vis Check", &g.isvis);

        }
        ImGui::Checkbox(_("AimAssist"), &g.AimAssist);
        if (g.AimAssist) {

            ImGui::Checkbox("Bezier Editor", &g.BezierEditor);
            if (g.BezierEditor) DrawBezierEditor(g.aimCurve);
            ImGui::SliderFloat("Fov", &g.AA_AimFov, 0.0f, 1000.0f, "%.0f R");
            ImGui::Checkbox("Right Click Only", &g.AA_AimInOnly);
            ImGui::Checkbox("Smoothing", &g.AA_EnableSmoothing);
            if (g.AA_EnableSmoothing)
            {
                ImGui::SliderFloat("Smoothing", &g.AA_Smoothing, 0.1f, 1.0f, "%0.1f");
            }
            ImGui::SliderFloat("Assist Randomness", &g.AssistRandomness, 0.f, 20.f, "%.1f");
            ImGui::Checkbox("Vis Check", &g.AA_isvis);
        }

        ImGui::EndChild();

        ImGui::NextColumn();

        // Second column - Texts
        ImGui::BeginChild("##AimbotSettings", ImVec2(0, 150), true, ImGuiWindowFlags_NoScrollbar);
        ImVec2 TextschildSize = ImGui::GetWindowSize();
        const char* Textstext = "Aimbot Settings";
        ImVec2 TextstextSize = ImGui::CalcTextSize(text);
        float TextstextX = (TextschildSize.x - TextstextSize.x) / 2.0f; // Center X
        float TextstextY = 10.0f; // Padding from the top

        // Position the text
        ImGui::SetCursorPos(ImVec2(TextstextX, TextstextY));
        ImGui::Text("%s", Textstext);
        ImGui::Separator();
        // ImGui::Checkbox("Weapons", &enableWeapons);

        if (ImGui::BeginCombo("Select Target Mode", g.TargetMode == 0 ? "Fov" : g.TargetMode == 1 ? "Health" : "Fov"))
        {
            if (ImGui::Selectable("Target By FOV Circle", g.TargetMode == 0)) {
                g.TargetMode = 0;

            }
            if (ImGui::Selectable("Target By Health", g.TargetMode == 1)) {
                g.TargetMode = 1;

            }
            ImGui::EndCombo();
        }
        if (ImGui::BeginCombo("Target Bone", g.TargettedBone == 0 ? "Head" : g.TargettedBone == 7 ? "Neck" : "Hip")) {
            if (ImGui::Selectable("Target Head", g.TargettedBone == 0)) {
                g.TargettedBone = 0;

            }
            if (ImGui::Selectable("Target Neck", g.TargettedBone == 7)) {
                g.TargettedBone = 7;

            }
            if (ImGui::Selectable("Target Hip", g.TargettedBone == 8)) {
                g.TargettedBone = 8;

            }
            ImGui::EndCombo();
        }

        ImGui::EndChild();

        ImGui::Columns(1);

        ImGui::Spacing();

        ImGui::Columns(2, nullptr, false);

        ImGui::BeginChild("##Others", ImVec2(0, 150), true, ImGuiWindowFlags_NoScrollbar);
        ImVec2 OtherschildSize = ImGui::GetWindowSize();
        const char* Otherstext = "Others";
        ImVec2 OtherstextSize = ImGui::CalcTextSize(Otherstext);
        float OtherstextX = (OtherschildSize.x - OtherstextSize.x) / 2.0f; 
        float OtherstextY = 10.0f; 

        ImGui::SetCursorPos(ImVec2(OtherstextX, OtherstextY));
        ImGui::Text("%s", Otherstext);
        ImGui::Separator();
        ImGui::EndChild();

        ImGui::NextColumn();

        ImGui::BeginChild("##Filters", ImVec2(0, 150), true, ImGuiWindowFlags_NoScrollbar);
        ImVec2 FilterschildSize = ImGui::GetWindowSize();
        const char* Filterstext = "Filters";
        ImVec2 FilterstextSize = ImGui::CalcTextSize(Filterstext);
        float FilterstextX = (FilterschildSize.x - FilterstextSize.x) / 2.0f;
        float FilterstextY = 10.0f;

        ImGui::SetCursorPos(ImVec2(FilterstextX, FilterstextY));
        ImGui::Text("%s", Filterstext);
        ImGui::Separator();

        ImGui::Checkbox("Skibidi", &g.HEALTHGOD);
        
        

        /*  ImGui::SliderFloat("Distance Filter", &sliderValue, 0.0f, 1000.0f, "%.0f m");
          ImGui::Checkbox("Draw Peds", &enableDrawPeds);
          ImGui::Checkbox("Draw Dead", &enableDrawDead);
          ImGui::Checkbox("Draw Epic Weapons", &enableDrawEpicWeapons);*/
        ImGui::EndChild();

        ImGui::Columns(1);

        // Tabs


        ImGui::End();
        break;
    }
    case 1: // ESP
    {
        static int index_child_2 = 0;

        ImGui::Begin("##MainWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowSize(ImVec2(700, 400));
        ImGui::BeginChild(_("##ButtonChild"), ImVec2(680.f, 60.f), true);
        for (int i = 0; i < VisualTitleList.size(); i++)
        {
            static float width = (ImGui::GetContentRegionAvail().x / 3.f) - 6.f;
            if (ImGui::Button(VisualTitleList[i].c_str(), ImVec2(width, 35.f)))
                index_child_2 = i;


            if (i != VisualTitleList.size() - 1)
                ImGui::SameLine();

        }
        ImGui::EndChild();

        // Tabs

        switch (index_child_2) {
        case 0:
        {
            ImGui::Columns(2, nullptr, false);

            ImGui::BeginChild("##Boxes", ImVec2(0, 150), true, ImGuiWindowFlags_NoScrollbar);


            ImVec2 BoxeschildSize = ImGui::GetWindowSize();
            const char* Boxestext = "Boxes";
            ImVec2 BoxestextSize = ImGui::CalcTextSize(text);
            float BoxestextX = (BoxeschildSize.x - BoxestextSize.x) / 2.0f; 
            float BoxestextY = 10.0f;

            ImGui::SetCursorPos(ImVec2(BoxestextX, BoxestextY));
            ImGui::Text("%s", Boxestext);

            ImGui::Separator();
            ImGui::Checkbox("Boxes", &g.ESP_Box);
            if (g.ESP_Box) {
                ImGui::Checkbox("Outline", &g.ESP_Box_Outline);
                if (g.ESP_Box_Outline) {
                    ImGui::SliderFloat("Outline Thickness", &g.ESP_Box_Outline_Thickness, 1.f, 10.f, "%.1f");
                }
                ImGui::SliderFloat("Box Thickness", &g.ESP_Box_Thickness, 1.f, 10.f, "%.1f");
                if (ImGui::BeginCombo("Select Mode", g.ESP_Box_Option == 0 ? "Basic" : g.ESP_Box_Option == 1 ? "Filled" : "Corner")) {
                    if (ImGui::Selectable("Basic 2d box", g.ESP_Box_Option == 0)) {
                        g.ESP_Box_Option = 0;

                    }
                    if (ImGui::Selectable("Filled 2d box", g.ESP_Box_Option == 1)) {
                        g.ESP_Box_Option = 1;

                    }
                    if (ImGui::Selectable("Corner's of 2d box", g.ESP_Box_Option == 2)) {
                        g.ESP_Box_Option = 2;

                    }
                    ImGui::EndCombo();
                }
            }
            switch (g.ESP_Box_Option) {
            case 0:
                break;
            case 1:
                ImGui::SliderFloat("Opacity", &g.ESP_Box_Filled_Opacity, 0.1f, 1.f, "%0.01f");
                break;
            case 2:
                ImGui::SliderFloat("Length", &g.ESP_Corner_Length, 15.5f, 50.f, "%0.5f");
                break;
            }

            ImGui::EndChild();

            ImGui::NextColumn();

            ImGui::BeginChild("##Texts", ImVec2(0, 150), true, ImGuiWindowFlags_NoScrollbar);
            ImVec2 TextschildSize = ImGui::GetWindowSize();
            const char* Textstext = "Texts";
            ImVec2 TextstextSize = ImGui::CalcTextSize(text);
            float TextstextX = (TextschildSize.x - TextstextSize.x) / 2.0f; 
            float TextstextY = 10.0f; 

            ImGui::SetCursorPos(ImVec2(TextstextX, TextstextY));
            ImGui::Text("%s", Textstext);
            ImGui::Separator();
            // ImGui::Checkbox("Weapons", &enableWeapons);
            ImGui::Checkbox("ID", &g.ESP_Name);
            ImGui::Checkbox("Distance", &g.ESP_Distance);
            ImGui::EndChild();

            ImGui::Columns(1);

            ImGui::Spacing();

            // Bottom rows
            ImGui::Columns(2, nullptr, false);

            // First bottom column - Others
            ImGui::BeginChild("##Others", ImVec2(0, 150), true, ImGuiWindowFlags_NoScrollbar);
            ImVec2 OtherschildSize = ImGui::GetWindowSize();
            const char* Otherstext = "Others";
            ImVec2 OtherstextSize = ImGui::CalcTextSize(Otherstext);
            float OtherstextX = (OtherschildSize.x - OtherstextSize.x) / 2.0f; // Center X
            float OtherstextY = 10.0f; // Padding from the top

            // Position the text
            ImGui::SetCursorPos(ImVec2(OtherstextX, OtherstextY));
            ImGui::Text("%s", Otherstext);
            ImGui::Separator();
            ImGui::Checkbox("Lines", &g.ESP_Line);
            if (g.ESP_Line) {
                if (ImGui::BeginCombo("Select Mode", g.ESP_Line_Pos == 0 ? "Top" : g.ESP_Line_Pos == 1 ? "Middle" : "Bottom")) {
                    if (ImGui::Selectable("Top of the Screen", g.ESP_Line_Pos == 0)) {
                        g.ESP_Line_Pos = 0;
                    }
                    if (ImGui::Selectable("Middle of the Screen", g.ESP_Line_Pos == 1)) {
                        g.ESP_Line_Pos = 1;
                    }
                    if (ImGui::Selectable("Bottom of the Screen", g.ESP_Line_Pos == 2)) {
                        g.ESP_Line_Pos = 2;
                    }
                    ImGui::EndCombo();
                }
            }
            ImGui::Checkbox("Skeleton", &g.ESP_Skeleton);
            if (g.ESP_Skeleton) {
                ImGui::SliderFloat("Thickness", &g.ESP_Skeleton_thickness, 1.f, 15.f, "%0.1f");
                ImGui::Checkbox("Outline", &g.ESP_SK_Outline);
                if (g.ESP_SK_Outline) {
                    ImGui::SliderFloat("Outline Thickness", &g.ESP_Skeleton_Outline_thickness, 1.f, 15.f, "%0.1f");
                }
            }
            ImGui::Checkbox("Health Bar", &g.ESP_HealthBar);
            //ImGui::Checkbox("Armor Bar", &g.esp);
            ImGui::EndChild();

            ImGui::NextColumn();

            // Second bottom column - Filters
            ImGui::BeginChild("##Filters", ImVec2(0, 150), true, ImGuiWindowFlags_NoScrollbar);
            ImVec2 FilterschildSize = ImGui::GetWindowSize();
            const char* Filterstext = "Filters";
            ImVec2 FilterstextSize = ImGui::CalcTextSize(Filterstext);
            float FilterstextX = (FilterschildSize.x - FilterstextSize.x) / 2.0f; // Center X
            float FilterstextY = 10.0f; // Padding from the top

            // Position the text
            ImGui::SetCursorPos(ImVec2(FilterstextX, FilterstextY));
            ImGui::Text("%s", Filterstext);
            ImGui::Separator();
            ImGui::SliderFloat("Distance Filter", &g.ESP_MaxDistance, 0.0f, 1000.0f, "%.0f m");
            ImGui::Checkbox("Draw Peds", &g.drawNpc);
            ImGui::Checkbox("Draw Dead", &g.drawDead);
            //ImGui::Checkbox("Draw Epic Weapons", &enableDrawEpicWeapons);
            ImGui::EndChild();

            ImGui::Columns(1);

            break;
        }
        case 1: // Color
            ImGui::ColorEdit4(_("Line"), &ESP_Line.Value.x);
            ImGui::ColorEdit4(_("NPC"), &ESP_NPC.Value.x);
            ImGui::ColorEdit4(_("Player"), &ESP_Player.Value.x);
            ImGui::ColorEdit4(_("Player Outline"), &ESP_Player_outline.Value.x);
            ImGui::ColorEdit4(_("Box Filled"), &ESP_Box_Filled.Value.x);
            ImGui::ColorEdit4(_("Skeleton"), &ESP_Skeleton.Value.x);
            ImGui::ColorEdit4(_("Skeleton Outline"), &ESP_Skeleton_outline.Value.x);

            break;
        case 2: // Builder IDK Yet
            ImGui::Text("Builder Content");
            break;

        }
        ImGui::End();
    }

    break;
    case 2: // MISC

    {

        ImGui::Begin("##MainWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowSize(ImVec2(700, 350));
        ImGui::Columns(2, nullptr, false);
        // First column - Boxes
        ImGui::BeginChild("##Gun Mods", ImVec2(0, 150), true, ImGuiWindowFlags_NoScrollbar);
        // Center text horizontally


        ImVec2 BoxeschildSize = ImGui::GetWindowSize();
        const char* Boxestext = "Gun Mods";
        ImVec2 BoxestextSize = ImGui::CalcTextSize(text);
        float BoxestextX = (BoxeschildSize.x - BoxestextSize.x) / 2.0f; // Center X
        float BoxestextY = 10.0f; // Padding from the top

        // Position the text
        ImGui::SetCursorPos(ImVec2(BoxestextX, BoxestextY));
        ImGui::Text("%s", Boxestext);

        ImGui::Separator();
        /* ImGui::Checkbox(_("NoRecoil"), &g.NoRecoil);
         if (g.NoRecoil) {
             ImGui::SliderFloat("Recoil Amount", &g.recoilAmount, 0.f, 2.f, "%.1f");
         }

         ImGui::Checkbox(_("NoSpread"), &g.NoSpread);
         if (g.NoSpread) {
             ImGui::SliderFloat("Spread Amount", &g.spreadAmount, 0.f, 2.f, "%.1f");
         }
         ImGui::Checkbox(_("RangeBypass"), &g.RangeBypass);
         ImGui::Checkbox(_("FastReload"), &g.FastReload);
         if (g.FastReload)
             ImGui::SliderFloat(_("Reload Delay"), &g.ReloadSpeed, 1, 10.f, "%.1f");*/
        ImGui::EndChild();

        ImGui::NextColumn();

        // Second column - Texts
        ImGui::BeginChild("##Overlay", ImVec2(0, 150), true, ImGuiWindowFlags_NoScrollbar);
        ImVec2 TextschildSize = ImGui::GetWindowSize();
        const char* Textstext = "Overlays";
        ImVec2 TextstextSize = ImGui::CalcTextSize(text);
        float TextstextX = (TextschildSize.x - TextstextSize.x) / 2.0f; // Center X
        float TextstextY = 10.0f; // Padding from the top

        // Position the text
        ImGui::SetCursorPos(ImVec2(TextstextX, TextstextY));
        ImGui::Text("%s", Textstext);
        ImGui::Separator();
        ImGui::Checkbox("Stream Proof", &g.StreamProof);
        ImGui::Checkbox("Crosshair", &g.Crosshair);
        // ImGui::Checkbox("Weapons", &enableWeapons);

        ImGui::EndChild();

        ImGui::Columns(1);

        ImGui::Spacing();

        // Bottom rows
        ImGui::Columns(2, nullptr, false);

        // First bottom column - Others
        ImGui::BeginChild("##Others", ImVec2(0, 150), true, ImGuiWindowFlags_NoScrollbar);
        ImVec2 OtherschildSize = ImGui::GetWindowSize();
        const char* Otherstext = "Others";
        ImVec2 OtherstextSize = ImGui::CalcTextSize(Otherstext);
        float OtherstextX = (OtherschildSize.x - OtherstextSize.x) / 2.0f; // Center X
        float OtherstextY = 10.0f; // Padding from the top

        // Position the text
        ImGui::SetCursorPos(ImVec2(OtherstextX, OtherstextY));
        ImGui::Text("%s", Otherstext);
        ImGui::Separator();
        //ImGui::Checkbox("Lines", &g.ESP_Line);
        //ImGui::Checkbox("Skeleton", &g.ESP_Skeleton);
        //ImGui::Checkbox("Health Bar", &g.ESP_HealthBar);
        //ImGui::Checkbox("Armor Bar", &g.esp);
        ImGui::EndChild();

        ImGui::NextColumn();

        // Second bottom column - Filters
        ImGui::BeginChild("##Filters", ImVec2(0, 150), true, ImGuiWindowFlags_NoScrollbar);
        ImVec2 FilterschildSize = ImGui::GetWindowSize();
        const char* Filterstext = "Filters";
        ImVec2 FilterstextSize = ImGui::CalcTextSize(Filterstext);
        float FilterstextX = (FilterschildSize.x - FilterstextSize.x) / 2.0f; // Center X
        float FilterstextY = 10.0f; // Padding from the top

        // Position the text
        ImGui::SetCursorPos(ImVec2(FilterstextX, FilterstextY));
        ImGui::Text("%s", Filterstext);
        ImGui::Separator();
        /*  ImGui::SliderFloat("Distance Filter", &sliderValue, 0.0f, 1000.0f, "%.0f m");
          ImGui::Checkbox("Draw Peds", &enableDrawPeds);
          ImGui::Checkbox("Draw Dead", &enableDrawDead);
          ImGui::Checkbox("Draw Epic Weapons", &enableDrawEpicWeapons);*/
        ImGui::EndChild();

        ImGui::Columns(1);

        // Tabs


        ImGui::End();
    }

    break;
    case 3:
        ImGui::Begin("##MainWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
        ImGui::SetWindowSize(ImVec2(700, 350));

        static char configName[256] = "";
        ImGui::InputText("Config Name", configName, sizeof(configName));

        if (ImGui::Button("Save"))
        {
            std::string filepath = configDirectory + "\\" + std::string(configName) + ".json";
            save_to_file(filepath);
            RefreshConfigList();
        }

        ImGui::SameLine();
        if (ImGui::Button("Load") && !selectedConfig.empty())
        {
            std::string filepath = configDirectory + "\\" + selectedConfig;
            load_from_file(filepath);
        }

        ImGui::SameLine();
        if (ImGui::Button("Override") && !selectedConfig.empty())
        {
            std::string filepath = configDirectory + "\\" + selectedConfig;
            save_to_file(filepath);
        }

        ImGui::SameLine();
        if (ImGui::Button("Rename") && !selectedConfig.empty() && configName != "")
        {
            std::string oldPath = configDirectory + "\\" + selectedConfig;
            std::string newPath = configDirectory + "\\" + std::string(configName) + ".json";
            if (fs::exists(oldPath))
            {
                fs::rename(oldPath, newPath);
                RefreshConfigList();
            }
        }


        ImGui::SameLine();
        if (ImGui::Button("Delete") && !selectedConfig.empty())
        {
            std::string filepath = configDirectory + "\\" + selectedConfig;
            if (fs::exists(filepath))
            {
                fs::remove(filepath);
                RefreshConfigList();
            }
        }

        if (ImGui::BeginListBox("Configs"))
        {
            for (const auto& file : configFiles)
            {
                bool isSelected = (file == selectedConfig);
                if (ImGui::Selectable(file.c_str(), isSelected))
                {
                    selectedConfig = file;
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }

        ImGui::End();
    }


    ImGui::End();

}