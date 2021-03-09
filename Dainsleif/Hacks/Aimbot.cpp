#include "Aimbot.h"

const double PI = 3.14159265358;
float aimSmoothness = 0.2f;
float range;

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

Player* GetClosestEnemyFromCrosshair(std::vector<Player*> playerList, Player* localPlayer)
{
    float closestDistance = 1000000.f;
    int closestPlayerIndex = -1;
    auto* viewAngles = reinterpret_cast<Vector3*>(*reinterpret_cast<uintptr_t*>(Modules::engine + dwClientState) + dwClientState_ViewAngles);
    for (int i = 0; i < playerList.size(); ++i)
    {
        Vector3 delta{};

        if (!playerList[i]->GetBoneMatrix()) continue; //null pointer check

        Vector3 playerHeadPosition = playerList[i]->GetBonePosition();

        GetDistance(playerHeadPosition, localPlayer->GetHeadPosition(), delta);
        float yaw = atan2(delta.y, delta.x) * (180 / static_cast<float>(PI));
        float yawDistance = fabs(yaw - viewAngles->y);

        if (yawDistance < closestDistance) {
            closestDistance = yawDistance;
            closestPlayerIndex = i;
        }
    }
    if (closestPlayerIndex == -1)
    {
        return nullptr;
    }
    return playerList[closestPlayerIndex];
}

void Aimbot::Run(std::vector<Player*> playerList)
{
    auto isAiming = *reinterpret_cast<bool*>(*reinterpret_cast<uintptr_t*>(Modules::client + 0x00D8B2DC) + 0x3928);

    Player* localPlayer = Player::GetLocalPlayer();
    static const WeaponID rejectWeaponList[3] = {SR_SSG08, SR_AWP, SR_G3SG1};
    Weapon* activeWeapon = localPlayer->GetActiveWeapon();
    WeaponID activeWeaponID = activeWeapon->GetWeaponID();
    for (WeaponID rejW : rejectWeaponList) {
        if (rejW == activeWeaponID && !isAiming) {
            return;
        }
    }
    static auto* viewAngles = reinterpret_cast<Vector3*>(*reinterpret_cast<uintptr_t*>(Modules::engine + dwClientState) + dwClientState_ViewAngles);

    Player* closestEnt = GetClosestEnemyFromCrosshair(playerList, localPlayer);
    if (!closestEnt || closestEnt->IsDormant())
        return;

    Vector3 delta{};
    float hypotenuse = GetDistance(closestEnt->GetBonePosition(), localPlayer->GetHeadPosition(), delta);
    float pitch = -asin(delta.z / hypotenuse) * (180 / static_cast<float>(PI));
    float yaw = atan2(delta.y, delta.x) * (180 / static_cast<float>(PI));

    if (pitch >= -89 && pitch <= 89 && yaw >= -180 && yaw <= 180)
    {
        float pitchDistance = fabs(pitch - viewAngles->x);
        float yawDistance = fabs(yaw - viewAngles->y);
        if (pitchDistance >= range || yawDistance >= range) {
            return;
        }

        float num = aimSmoothness / max(pitchDistance, yawDistance);
        float x = num * min(pitchDistance, yawDistance);

        /*
        aimSmoothness is a base of how smooth the aim pulling should be.
        num * max == 0.5f.
        Bigger:0.5 = Smoller:x
        */
        float pf, yf;
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