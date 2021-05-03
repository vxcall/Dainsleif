#include "Bunnyhop.h"

void Bhop::ForceJump()
{
	auto* forceJump = reinterpret_cast<int*>(Modules::client + dwForceJump);
	*forceJump = 6;
}

void Bhop::Run()
{
	Player* localPlayer = Player::GetLocalPlayer();
	uintptr_t flags = localPlayer->GetFlags();
	if (flags & (1 << 0))
	{
		Bhop::ForceJump();
	}
}
