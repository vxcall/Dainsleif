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