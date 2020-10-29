#pragma once
#include "../Utils.h"
#include "../Vector.h"

class CUserCmd;
struct CVerifiedUserCmd;

class CInput
{
public:
    void* vTable;
    bool trackIrAvailable;
    bool mouseInitialized;
    bool mouseActive;
    bool joyStickAdvancedInit;
    char m_pad_0x08[ 0x2C ];
    void* keys;
    char m_pad_0x38[ 0x64 ];
    int m_pad_0x41;
    int m_pad_0x42;
    int m_pad_0x43;
    int m_pad_0x44;
    bool cameraInterceptingMouse;
    bool cameraInThirdperson;
    bool cameraMovingWithMouse;
    Vector3 cameraOffset;
    bool cameraDistanceMove;
    int cameraOldX;
    int cameraOldY;
    int cameraX;
    int cameraY;
    bool cameraIsOrthographic;
    Vector3 previousViewAngles;
    Vector3 previousViewAnglesTilt;
    float lastForwardMove;
    int clearInputState;
    CUserCmd* userCommands;
    CVerifiedUserCmd* verifiedUserCommands;

    CALL_VFUNC(39, ResetInputState(), void(__thiscall*)(CInput*)) ()
};
