#include "../../Cheat.h"

void Cheat::AimAssist()
{
    BezierCurve aimCurve;
    g.aimCurve = aimCurve;
    while (g.Run)
    {
        CPed target = FindBestTarget();
        Matrix ViewMatrix = m.SysRead<Matrix>(ViewPort + 0x24C);

        if (g.AimAssist)
        {
            if (g.AimInOnly && IsKeyDown(g.AimKey0) || !g.AimInOnly && IsKeyDown(g.AimKey1))
            {
                Vector3 WriteAngle;
                uintptr_t camera = m.SysRead<uintptr_t>(m.BaseAddress + offset::Camera);

                if (!Vec3_Empty(target.BoneList[g.TargettedBone]))
                {
                    Vector3 ViewAngle = m.SysRead<Vector3>(camera + 0x3D0);
                    Vector3 CameraPos = m.SysRead<Vector3>(camera + 0x60);

                    Vector3 TargetAngle = CalcAngle(CameraPos, target.BoneList[g.TargettedBone]);
                    NormalizeAngles(TargetAngle);

                    Vector3 Delta = TargetAngle - ViewAngle;
                    NormalizeAngles(Delta);

                    float progress = g.Smoothing;
                    ImVec2 interpolatedPoint = g.aimCurve.Interpolate(progress);

                    Delta.x *= interpolatedPoint.x;
                    Delta.y *= interpolatedPoint.y;

                    WriteAngle = ViewAngle + Delta;
                    NormalizeAngles(WriteAngle);

                    if (!Vec3_Empty(WriteAngle))
                    {
                        m.SysWrite<Vector3>(camera + 0x3D0, WriteAngle);
                    }
                }
            }

            Sleep(1);
        }
    }
}