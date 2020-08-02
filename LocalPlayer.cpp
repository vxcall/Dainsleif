#include "pch.h"
#include "LocalPlayer.h"

LocalPlayer* GetLocalPlayer(uintptr_t moduleBase)
{
	return reinterpret_cast<LocalPlayer*>((moduleBase + dwLocalPlayer)); //get local player address and cast it to my original class type
}

float GetDistance(Vector3 targetPos, Vector3 basePos, Vector3& deltaVector)
{
    deltaVector = targetPos - basePos;
    return sqrt(deltaVector.x * deltaVector.x + deltaVector.y * deltaVector.y + deltaVector.z * deltaVector.z);
}

Vector3* LocalPlayer::GetHeadPosition()
{
	Vector3 bp = *(this->GetBodyPosition()); //get position and dereference it to calculate later on.
	Vector3 vo = *(this->GetViewOffset()); //get viewoffset and dereference it to calculate later on.
	Vector3* headPosition = &(bp + vo); //calculate them and store the result into pointer variable.
	return headPosition;
}

void LocalPlayer::SetFOV(int fov)
{
    *reinterpret_cast<int*>(*(uintptr_t*)this + m_iFOV) = fov;
}



Vector3 oldPunch = { 0, 0, 0 };
int oldShotCount = 0;

void LocalPlayer::NeutralizeRecoil() {
    static uintptr_t engineModule = reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll"));

    int* ShotCount = reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(this) + m_iShotsFired);

    if (*ShotCount >= 1) {
        if (*ShotCount != oldShotCount) {
            //This refers to the cursor position after local player shot. Bullet's gonna be shot out over the cursor by twice.
            Vector3 *AimPunchAngle = reinterpret_cast<Vector3 *>(*reinterpret_cast<uintptr_t *>(this) + m_aimPunchAngle);
            Vector3 *viewAngle = reinterpret_cast<Vector3 *>((*reinterpret_cast<uintptr_t *>((engineModule + dwClientState)) + dwClientState_ViewAngles));
            Vector3 rcsAngle;
            rcsAngle.y = viewAngle->y + (oldPunch.y - AimPunchAngle->y * 2.f);
            rcsAngle.x = viewAngle->x + (oldPunch.x - AimPunchAngle->x * 2.f);

            while (viewAngle->y > 180)
                viewAngle->y -= 360;
            while (viewAngle->y < -180)
                viewAngle->y += 360;

            if (viewAngle->x > 89.f)
                viewAngle->x = 89.f;
            else if (viewAngle->x < -89.f)
                viewAngle->x = -89.f;

            oldPunch.y = AimPunchAngle->y * 2.f;
            oldPunch.x = AimPunchAngle->x * 2.f;
            viewAngle->y = rcsAngle.y;
            viewAngle->x = rcsAngle.x;
            oldShotCount = *ShotCount;
        }
    } else {
        oldPunch = {0, 0, 0};
        oldShotCount = 0;
    }
}

//If Trigger bot is on, Aimbot have to need this somehow.
bool isTriggerBotON = false;
void LocalPlayer::AutoPullTrigger(std::vector<Entity*> entityList)
{
    int crosshairID = *reinterpret_cast<int*>(*reinterpret_cast<uintptr_t*>(this) + m_iCrosshairId); //this int value holds index of entity list.
    if (crosshairID != 0) {
        //When you kill all enemy, it's somehow gonna be a number more than 300.
        if (crosshairID - 2 > 9) return;
        if (this->GetTeam() != entityList[crosshairID - 2]->GetTeam()) {
            mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, 0, 0);
        }
    }
}