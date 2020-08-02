#include "../pch.h"
#include "../LocalPlayer.h"
#include "Aimbot.h"

float aimSmoothness = 0.2f;

// sign() checks if the argument is positive or negative
int sign(float A)
{
    return (A > 0) - (A < 0);
}

const double PI = 3.14159265358;
void Aimbot::Run(Vector3 TargetsHeadPosition, LocalPlayer* lp)
{
    static uintptr_t engineModule = reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll"));
    static Vector3* viewAngles = reinterpret_cast<Vector3*>((*reinterpret_cast<uintptr_t*>((engineModule + dwClientState)) + dwClientState_ViewAngles));
    Vector3 delta;
    float hypotenuse = GetDistance(TargetsHeadPosition, *lp->GetHeadPosition(), delta);
    float pitch = -asin(delta.z / hypotenuse) * (180 / static_cast<float>(PI));
    float yaw = atan2(delta.y, delta.x) * (180 / static_cast<float>(PI));

    if (pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180)
    {
        float pitchDistance = fabs(pitch - viewAngles->x);
        float yawDistance = fabs(yaw - viewAngles->y);
        if (pitchDistance >= 11 || yawDistance >= 11) {
            return;
        }

        float num = aimSmoothness / max(pitchDistance, yawDistance);
        float x = num * min(pitchDistance, yawDistance);

        /*
        aimSmoothness is a base of how smooth the aim pulling should be.
        num * max == 0.5f.
        Bigger:0.5 = Smoller:x
        */
        float pf;
        float yf;
        if (pitchDistance > yawDistance)
        {
            pf = aimSmoothness;
            yf = x;
        } else {
            pf = x;
            yf = aimSmoothness;
        }

        float rangeAimFix = aimSmoothness * 0.5f; //rangeAimFix holds the value representing area around enemy's head that allows viewAngle to be free.
        if (aimSmoothness <= 0.2)
            rangeAimFix = 0.1f;

        if (pitchDistance > rangeAimFix) {
            if (viewAngles->x < pitch)  //my view is smaller than pitch.
            {
                viewAngles->x += pf;
            }
            else if (viewAngles->x > pitch)
            {
                viewAngles->x -= pf;
            }
        }

        if (yawDistance > rangeAimFix) {
            if (viewAngles->y < yaw)
            {
                if (sign(viewAngles->y) == -1 && sign(yaw) == 1 && viewAngles->y <= -90) //When yaw is like 170 and viewAngle steps over -180
                {
                    viewAngles->y -= yf;
                } else {
                    viewAngles->y += yf;
                }
            } else if (viewAngles->y > yaw) {
                if (sign(viewAngles->y) == 1 && sign(yaw) == -1 && viewAngles->y >= 90)  //When yaw is like -170 and viewAngle steps over 180
                {
                    viewAngles->y += yf;
                } else {
                    viewAngles->y -= yf;
                }

            }
        }
    }
}