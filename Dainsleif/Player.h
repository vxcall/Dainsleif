#pragma once
#include "pch.h"
#include "Entity.h"
#include "Weapon.h"

class Player : public Entity
{
public:
    static Player* GetLocalPlayer();

    static std::vector<Player*> GetAll();

    static std::vector<Player*> GetLivingOpponents();

    static int GetMaxPlayers();

    uintptr_t GetBoneMatrix();

    uintptr_t GetGlowIndex();

    //GetBodyPosition retrieves where player's body is as vector3.
    Vector3 GetBodyPosition();

    //GetViewOffset returns the distance between the body position and the actual sight of player.
    Vector3 GetViewOffset();

    Vector3 GetAimPunchAngle();

    Vector3 GetBonePosition();

    //GetHeadPosition calculates head position by view offset and body position.
	Vector3 GetHeadPosition();

    //GetHealth retrieves player's health.
    int GetHealth();

    //GetTeam returns teamNumber so that I can distinguish either the player is friendly or hostile.
    int GetTeam();

    int GetShotsFired();

    int GetCrosshairID();

    Weapon* GetActiveWeapon();

    void SetFOV(int fov);
};