#pragma once
#include "ImGui/imgui.h"

struct BezierCurve
{
    ImVec2 p0 = ImVec2(0.0f, 0.0f);
    ImVec2 p1 = ImVec2(0.25f, 0.5f);
    ImVec2 p2 = ImVec2(0.75f, 0.5f);
    ImVec2 p3 = ImVec2(1.0f, 1.0f);

    ImVec2 Interpolate(float t) const
    {
        float u = 1.0f - t;
        float tt = t * t;
        float uu = u * u;
        float uuu = uu * u;
        float ttt = tt * t;

        ImVec2 point;
        point.x = uuu * p0.x + 3 * uu * t * p1.x + 3 * u * tt * p2.x + ttt * p3.x;
        point.y = uuu * p0.y + 3 * uu * t * p1.y + 3 * u * tt * p2.y + ttt * p3.y;

        return point;
    }
};
