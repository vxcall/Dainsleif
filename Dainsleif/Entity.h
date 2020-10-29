#pragma once
#include "pch.h"
#include "ClientClass.h"

class Entity
{
public:
    static Entity* GetByIndex(int index);

    static std::vector<Entity*> GetAll();

    template <typename T>
    T ReadValue(std::ptrdiff_t offset)
    {
        return *reinterpret_cast<T*>(this + offset);
    }

    template <typename T>
    void WriteValue(std::ptrdiff_t offset, T value)
    {
        *reinterpret_cast<T*>(this + offset) = value;
    }

    template <typename T>
    T Cast()
    {
        return reinterpret_cast<T>(this);
    }

    void* GetClientNetworkable();
    ClientClass* GetClientClass();
    bool IsDormant();
};

struct EntInfo
{
    Entity* m_pEntity;
    int m_SerialNumber;
    EntInfo* m_pPrev;
    EntInfo* m_pNext;
};