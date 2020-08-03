#include "../pch.h"
#include "../LocalPlayer.h"
#include "Aimbot.h"

float aimSmoothness = 0.2f;
extern uintptr_t moduleBase;
const double PI = 3.14159265358;

// sign() checks if the argument is positive or negative
int sign(float A)
{
    return (A > 0) - (A < 0);
}

float GetDistance(Vector3 targetPos, Vector3 basePos, Vector3& deltaVector)
{
    deltaVector = targetPos - basePos;
    return sqrt(deltaVector.x * deltaVector.x + deltaVector.y * deltaVector.y + deltaVector.z * deltaVector.z);
}

Entity* GetClosestEnemyFromCrosshair(std::vector<Entity*> entityList, LocalPlayer* lp)
{
    static uintptr_t engineModule = reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll"));
    float closestDistance = 1000000;
    int closestEntityIndex = -1;
    Vector3* viewAngles = reinterpret_cast<Vector3*>((*reinterpret_cast<uintptr_t*>((engineModule + dwClientState)) + dwClientState_ViewAngles));
    for (int i = 0; i < static_cast<int>(entityList.size()); ++i)
    {
        Vector3 delta;

        Vector3* entityHeadPosition = entityList[i]->GetBonePosition();
        if (!entityHeadPosition) continue; //null pointer check

        GetDistance(*entityHeadPosition, *lp->GetHeadPosition(), delta);
        float yaw = atan2(delta.y, delta.x) * (180 / static_cast<float>(PI));
        int yawDistance = abs(static_cast<int>(yaw - viewAngles->y));

        if (yawDistance < closestDistance) {
            closestDistance = yawDistance;
            closestEntityIndex = i;
        }
    }
    if (closestEntityIndex == -1)
    {
        return nullptr;
    }
    return entityList[closestEntityIndex];
}

// FilterOutIrrelevant basically filter out the dead enemies and allies from entityList.
void FilterOutIrrelevant(std::vector<Entity*>& entityList, LocalPlayer* lp)
{
    for (int i = 0;i < static_cast<int>(entityList.size());) {
        if (entityList[i]->GetTeam() == lp->GetTeam() || !*entityList[i]->GetHealth()) {
            entityList.erase(entityList.begin() + i);
        } else {
            ++i;
        }
    }
}

void Aimbot::Run(std::vector<Entity*> entityList)
{
    LocalPlayer* lp = GetLocalPlayer();

    FilterOutIrrelevant(entityList, lp);
    static uintptr_t engineModule = reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll"));
    static Vector3* viewAngles = reinterpret_cast<Vector3*>((*reinterpret_cast<uintptr_t*>((engineModule + dwClientState)) + dwClientState_ViewAngles));

    Entity* closestEnt = GetClosestEnemyFromCrosshair(entityList, lp);
    if (!closestEnt || *closestEnt->IsDormant())
        return;

    Vector3 delta;
    float hypotenuse = GetDistance(*closestEnt->GetBonePosition(), *lp->GetHeadPosition(), delta);
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