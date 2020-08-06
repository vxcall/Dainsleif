#include "pch.h"
#include "Weapon.h"

WeaponID Weapon::GetWeaponID()
{
    return ReadValue<WeaponID>(m_iItemDefinitionIndex);
}