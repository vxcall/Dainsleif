#include "pch.h"
#include "LocalPlayer.h"
#include "offsets.h"
#include "utility.h"
#include <iostream>
#include <Windows.h>
#include "vector3.h"


LocalPlayer* GetLocalPlayer(uintptr_t moduleBase)
{
	LocalPlayer* lp = (LocalPlayer*)(moduleBase + dwLocalPlayer); //get local player address and cast it to my original class type
	return lp;
}

Vector3* LocalPlayer::GetBodyPosition()
{
	return (Vector3*)(*(uintptr_t*)this + m_vecOrigin);
}

Vector3* LocalPlayer::GetViewOffset()
{
	return (Vector3*)(*(uintptr_t*)this + m_vecViewOffset);
}

Vector3* LocalPlayer::GetHeadPosition()
{
	Vector3 bp = *(this->GetBodyPosition()); //get position and dereference it to calculate later on.
	Vector3 vo = *(this->GetViewOffset()); //get viewoffset and dereference it to calculate later on.
	Vector3* headPosition = &(bp + vo); //calculate them and store the result into pointer variable.
	return headPosition;
}

int* LocalPlayer::GetHealth()
{
	return (int*)(*(uintptr_t*)this + m_iHealth);
}