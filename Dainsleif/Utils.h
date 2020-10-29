#pragma once
#include <cstddef>

namespace Utils
{
    template < typename T >
    T GetVirtualFunction ( void* baseClass, int index )
    {
        return ( *static_cast< T** > ( baseClass ) )[ index ];
    }

    template < typename T, typename ... Args >
    T CallVirtualFunction ( void* baseClass, int index, Args ... args )
    {
        return GetVirtualFunction< T(__thiscall*) (void*, Args ... ) > ( baseClass, index )(baseClass, args...);
    }
}

#define MEMBER_FUNC_ARGS(...) (this, __VA_ARGS__); };
#define CALL_VFUNC(index, func, type) __forceinline auto func { return Utils::GetVirtualFunction<type>(this, index) MEMBER_FUNC_ARGS

/*EXAMPLE OF USING CALL_VFUNC:
* PARAMS: index, func, type
* $param(index): the index of the virtual function you want to call.
* $param(func): the name of the function, and its parameters if any.
* $param(type): the type of the function (usually a __thiscall*, but others can be used aswell.)
* CALL_VFUNC(25, some_func(int arg1, int arg2), void(__thiscall*)(type*, int, int)) (arg1, arg2)
*/
