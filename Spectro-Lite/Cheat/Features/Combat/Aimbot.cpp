#include "../../Cheat.h"


void Cheat::AimBot()
{
    while (g.Run)
    {
        CPed target = FindBestTarget();
        Matrix ViewMatrix = m.SysRead<Matrix>(ViewPort + 0x24C);

        if (g.AimBot) {

            if (g.AimInOnly && IsKeyDown(g.AimKey0) || !g.AimInOnly && IsKeyDown(g.AimKey1))
            {
                Vector3 WriteAngle;
                uintptr_t camera = m.SysRead<uintptr_t>(m.BaseAddress + offset::Camera);
                uintptr_t Debug_ViewAngle = m.SysRead<uintptr_t>(camera + 0x3D0);
                uintptr_t Debug_CamPos = m.SysRead<uintptr_t>(camera + 0x60);
                OutputDebugStringA(!camera ? "Camera Pointer Invalid\n" : "Valid Camera Pointer\n");
                OutputDebugStringA(!Debug_ViewAngle ? "Debug_ViewAngle Pointer Invalid\n" : "Valid Debug_ViewAngle Pointer\n");
                OutputDebugStringA(!Debug_CamPos ? "Debug_CamPos Pointer Invalid\n" : "Valid Debug_CamPos Pointer\n");

                if (!Vec3_Empty(target.BoneList[g.TargettedBone]))
                {
                    Vector3 ViewAngle = m.SysRead<Vector3>(camera + 0x3D0);
                    Vector3 CameraPos = m.SysRead<Vector3>(camera + 0x60);
                    Vector3 CamPosFirst = m.SysRead<Vector3>(camera + 0x40);
                    Vector3 Angle;
                    if (CameraPos != Vector3(0, 0, 0)) {
                        Angle = CalcAngle(CameraPos, target.BoneList[g.TargettedBone]);
                    }
                    else {
                        Angle = CalcAngle(CamPosFirst, target.BoneList[g.TargettedBone]);
                    }

                    NormalizeAngles(Angle);
                    Vector3 Delta = Angle - ViewAngle;
                    NormalizeAngles(Delta);

                    // Add smoothing factor

                    if (g.EnableSmoothing)
                        WriteAngle = ViewAngle + (Delta * g.Smoothing);
                    else
                        WriteAngle = ViewAngle + Delta;
                    NormalizeAngles(WriteAngle);

                    if (!Vec3_Empty(WriteAngle))
                    {
                        m.SysWrite<Vector3>(camera + 0x3D0, WriteAngle);


                        //m.Write<Vector3>(camera + 0x3D0, WriteAngle);
                    }
                }
            }


            Sleep(1);
        }
    }
}