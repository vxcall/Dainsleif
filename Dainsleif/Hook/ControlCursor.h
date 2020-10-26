#pragma once

#include "../pch.h"
#include "Interface.h"
#include "../Utils.h"
#include "../PatternScanner.h"
#include "../Modules.h"
#include "../dllmain.h"

template<typename T>
T GetVirtualFunction(void* baseClass, int index);

class ISurface {
public:
    using fnUnlockCursor = void(__thiscall*)(ISurface*);
    void UnlockCursor()
    {

        GetVirtualFunction<fnUnlockCursor>(this, 66);
    }
};

class CUserCmd;
struct CVerifiedUserCmd;

struct CInput {
    using fnResetInputState = void(__thiscall*)(CInput*);
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
    void ResetInputState()
    {
        GetVirtualFunction<fnResetInputState>(this, 39);
    }
};

using tLockCursor = void(__thiscall*) (ISurface*);

void HookLockCursor();
