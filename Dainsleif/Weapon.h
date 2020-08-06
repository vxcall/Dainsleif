#pragma once
#include "pch.h"
#include "Entity.h"

enum WeaponID {
    NULLWEAPON = 0,
    KNIFE = 59,
    C4 = 49,

    HG_GLOCK = 4,
    HG_DUAL_BERETTAS = 2,
    HG_P250 = 36,
    HG_TEC9 = 30,
    HG_DESERT_EAGLE = 1,

    SG_NOVA = 35,
    SG_XM1014 = 25,
    SG_SAWED_OFF = 29,

    HEAVY_M249 = 14,
    HEAVY_NEGEV = 28,

    SMG_MAC10 = 17,
    SMG_MP7 = 33,
    SMG_UMP45 = 24,
    SMG_P90 = 19,
    SMG_PP_BIZON = 26,

    AR_GALIL = 13,
    AR_AK47 = 7,
    AR_SG553 = 39,

    SR_SSG08 = 40,
    SR_AWP = 9,
    SR_G3SG1 = 11,

    GN_MOLOTOV = 46,
    GN_DECOY = 47,
    GN_FLASH_ = 43,
    GN_HE = 44,
    GN_SMOKE = 45,

    ZEUS_X27 = 31,
};

class Weapon : public Entity
{
public:
    WeaponID GetWeaponID();
};