#pragma once
#include "../Player.h"

namespace Glow {
    void Run(Player* player);
}

struct GlowObject {
    int m_nNextFreeSlot;
    Entity* m_pEntity;
    float r;
    float g;
    float b;
    float a;
    bool m_bGlowAlphaCappedByRenderAlpha;
    std::byte pad0[0x3];
    float m_flGlowAlphaFunctionOfMaxVelocity;
    float m_flGlowAlphaMax;
    float m_flGlowPulseOverdrive;
    bool m_bRenderWhenOccluded;
    bool m_bRenderWhenUnoccluded;
    bool m_bFullBloomRender;
    std::byte pad1[0x1];
    int m_nFullBloomStencilTestValue;
    int m_nRenderStyle;
    int m_nSplitScreenSlot;
};