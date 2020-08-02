#include "pch.h"
#include "LocalPlayer.h"

uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));

LocalPlayer* GetLocalPlayer()
{
	return reinterpret_cast<LocalPlayer*>((moduleBase + dwLocalPlayer)); //get local player address and cast it to my original class type
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