#include "pch.h"
#include "Player.h"

Player* Player::GetLocalPlayer()
{
    return *reinterpret_cast<Player**>(Modules::client + dwLocalPlayer);
}

std::vector<Player*> Player::GetAll()
{
    std::vector<Player*> allPlayers;
    for (int i = 1; i <= GetMaxPlayers(); i++)
    {
        Entity* entity = Entity::GetByIndex(i);
        if (!entity || entity->GetClientClass()->m_ClassID != ClassID::CCSPlayer)
        {
            continue;
        }

        Player* player = entity->Cast<Player*>();
        allPlayers.push_back(player);
    }
    return allPlayers;
}

// FilterOutIrrelevant basically filter out the dead enemies and allies from playerList.
void FilterOutIrrelevant(std::vector<Player*>& playerList, Player* localPlayer)
{
    for (int i = 0;i < static_cast<int>(playerList.size());) {
        if (playerList[i]->GetTeam() == localPlayer->GetTeam() || !playerList[i]->GetHealth()) {
            playerList.erase(playerList.begin() + i);
        } else {
            ++i;
        }
    }
}
// FilterOutIrrelevant basically filter out the dead enemies and allies from playerList.
std::vector<Player*> Player::GetLivingOpponents() {
    Player* localPlayer = GetLocalPlayer();
    std::vector<Player*> playerList = GetAll();
    FilterOutIrrelevant(playerList, localPlayer);
    return playerList;
}

int Player::GetMaxPlayers()
{
    uintptr_t clientState = *reinterpret_cast<uintptr_t*>(Modules::engine + dwClientState);
    return *reinterpret_cast<int*>(clientState + dwClientState_MaxPlayer);
}

uintptr_t Player::GetBoneMatrix()
{
    return ReadValue<uintptr_t>(m_dwBoneMatrix);
}

uintptr_t Player::GetGlowIndex()
{
    return ReadValue<uintptr_t>(m_iGlowIndex);
}

Vector3 Player::GetBodyPosition()
{
    return ReadValue<Vector3>(m_vecOrigin);
}

Vector3 Player::GetViewOffset()
{
    return ReadValue<Vector3>(m_vecViewOffset);
}

Vector3 Player::GetAimPunchAngle()
{
    return ReadValue<Vector3>(m_aimPunchAngle);
}

#define boneID 8
Vector3 Player::GetBonePosition()
{
    uintptr_t boneMatrix = GetBoneMatrix();
    if (!boneMatrix) //When the game starts with bAimbot on, the game is gonna crash.
    {
        return {};
    }
    return {*reinterpret_cast<float*>(boneMatrix + 0x30 * boneID + 0x0C),
            *reinterpret_cast<float*>(boneMatrix + 0x30 * boneID + 0x1C),
            *reinterpret_cast<float*>(boneMatrix + 0x30 * boneID + 0x2C)};
}

Vector3 Player::GetHeadPosition()
{
    return GetBodyPosition() + GetViewOffset();
}

int Player::GetHealth()
{
    return ReadValue<int>(m_iHealth);
}

int Player::GetTeam()
{
    return ReadValue<int>(m_iTeamNum);
}

int Player::GetShotsFired()
{
    return ReadValue<int>(m_iShotsFired);
}

int Player::GetCrosshairID()
{
    return ReadValue<int>(m_iCrosshairId);
}

Weapon* Player::GetActiveWeapon()
{
    uintptr_t activeWeaponHandle = ReadValue<uintptr_t>(m_hActiveWeapon);
    int index = (activeWeaponHandle & 0xFFF) - 1;
    return Entity::GetByIndex(index)->Cast<Weapon*>();
}

void Player::SetFOV(int fov)
{
    if (this)
        WriteValue<int>(m_iFOV, fov);
}