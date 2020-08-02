#pragma once
#include "../Entity.h"
#include "../LocalPlayer.h"

namespace Glow {
    void Run(Entity* entity);
}

//This is a struct to treat glow stuff cleaner maybe XD.
struct GlowObject {
    float* Red;
    float* Green;
    float* Blue;
    float* Alpha;

    GlowObject(uintptr_t glowObjectManager, uintptr_t glowIndex)
    {
        Red = reinterpret_cast<float*>((glowObjectManager + ((glowIndex * 0x38) + 0x4)));
        Green = reinterpret_cast<float*>((glowObjectManager + ((glowIndex * 0x38) + 0x8)));
        Blue = reinterpret_cast<float*>((glowObjectManager + ((glowIndex * 0x38) + 0xC)));
        Alpha = reinterpret_cast<float*>((glowObjectManager + ((glowIndex * 0x38) + 0x10)));
    }
};