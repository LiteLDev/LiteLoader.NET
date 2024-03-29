#pragma once
#include <HookAPI.h>
#include <src/Main/DotNETGlobal.hpp>
#include <src/Module/Core/SecondaryRankPtr.hpp>

namespace LiteLoader::Hook {
    using LiteLoader::NET::SecondaryRankPtr;

    public ref class HookAPI __static
    {
    public:
        inline static int HookFunction(void* oldfunc, void** poutold, void* newfunc);
        inline static int HookFunction(nint_t oldfunc, SecondaryRankPtr poutold, nint_t newfunc);
        inline static void* dlsym_real(char const* name);
        inline static nint_t dlsym_real(System::String^ name);
        inline static uintptr_t findSig(String^ szSignature);
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        generic<typename RTN>
        where RTN : value struct
            inline static RTN VirtualCall(void const* _this, uintptr_t off) {
            return (*(RTN(**)(void const*))(*(uintptr_t*)_this + off))(_this);
        }

        generic<typename RTN, typename T0>
        where RTN : value struct
        where T0 : value struct
            inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0) {
            return (*(RTN(**)(void const*, T0))(*(uintptr_t*)_this + off))(_this, a0);
        }
        generic<typename RTN, typename T0, typename T1>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
            inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1) {
            return (*(RTN(**)(void const*, T0, T1))(*(uintptr_t*)_this + off))(_this, a0, a1);
        }
        generic<typename RTN, typename T0, typename T1, typename T2>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
            inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2) {
            return (*(RTN(**)(void const*, T0, T1, T2))(*(uintptr_t*)_this + off))(_this, a0, a1, a2);
        }
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
            inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3) {
            return (*(RTN(**)(void const*, T0, T1, T2, T3))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3);
        }
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
            inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
            return (*(RTN(**)(void const*, T0, T1, T2, T3, T4))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4);
        }
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
            inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
            return (*(RTN(**)(void const*, T0, T1, T2, T3, T4, T5))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4, a5);
        }
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
        where T6 : value struct
            inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
            return (*(RTN(**)(void const*, T0, T1, T2, T3, T4, T5, T6))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4, a5, a6);
        }
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
        where T6 : value struct
        where T7 : value struct
            inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
            return (*(RTN(**)(void const*, T0, T1, T2, T3, T4, T5, T6, T7))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4, a5, a6, a7);
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        inline static void Virtual_Call(void const* _this, uintptr_t off) {
            return (*(void(**)(void const*))(*(uintptr_t*)_this + off))(_this);
        }

        generic< typename T0>
        where T0 : value struct
            inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0) {
            return (*(void(**)(void const*, T0))(*(uintptr_t*)_this + off))(_this, a0);
        }
        generic< typename T0, typename T1>
        where T0 : value struct
        where T1 : value struct
            inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1) {
            return (*(void(**)(void const*, T0, T1))(*(uintptr_t*)_this + off))(_this, a0, a1);
        }
        generic< typename T0, typename T1, typename T2>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
            inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2) {
            return (*(void(**)(void const*, T0, T1, T2))(*(uintptr_t*)_this + off))(_this, a0, a1, a2);
        }
        generic< typename T0, typename T1, typename T2, typename T3>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
            inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3) {
            return (*(void(**)(void const*, T0, T1, T2, T3))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3);
        }
        generic< typename T0, typename T1, typename T2, typename T3, typename T4>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
            inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
            return (*(void(**)(void const*, T0, T1, T2, T3, T4))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4);
        }
        generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
            inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
            return (*(void(**)(void const*, T0, T1, T2, T3, T4, T5))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4, a5);
        }
        generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
        where T6 : value struct
            inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
            return (*(void(**)(void const*, T0, T1, T2, T3, T4, T5, T6))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4, a5, a6);
        }
        generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
        where T6 : value struct
        where T7 : value struct
            inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
            return (*(void(**)(void const*, T0, T1, T2, T3, T4, T5, T6, T7))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4, a5, a6, a7);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        generic<typename RTN>
        where RTN : value struct
            inline static RTN VirtualCall(nint_t _this, uintptr_t off) {
            return (*(RTN(**)(void const*))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer());
        }

        generic<typename RTN, typename T0>
        where RTN : value struct
        where T0 : value struct
            inline static RTN VirtualCall(nint_t _this, uintptr_t off, T0 a0) {
            return (*(RTN(**)(void const*, T0))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0);
        }
        generic<typename RTN, typename T0, typename T1>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
            inline static RTN VirtualCall(nint_t _this, uintptr_t off, T0 a0, T1 a1) {
            return (*(RTN(**)(void const*, T0, T1))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1);
        }
        generic<typename RTN, typename T0, typename T1, typename T2>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
            inline static RTN VirtualCall(nint_t _this, uintptr_t off, T0 a0, T1 a1, T2 a2) {
            return (*(RTN(**)(void const*, T0, T1, T2))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1, a2);
        }
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
            inline static RTN VirtualCall(nint_t _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3) {
            return (*(RTN(**)(void const*, T0, T1, T2, T3))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1, a2, a3);
        }
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
            inline static RTN VirtualCall(nint_t _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
            return (*(RTN(**)(void const*, T0, T1, T2, T3, T4))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1, a2, a3, a4);
        }
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
            inline static RTN VirtualCall(nint_t _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
            return (*(RTN(**)(void const*, T0, T1, T2, T3, T4, T5))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1, a2, a3, a4, a5);
        }
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
        where T6 : value struct
            inline static RTN VirtualCall(nint_t _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
            return (*(RTN(**)(void const*, T0, T1, T2, T3, T4, T5, T6))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1, a2, a3, a4, a5, a6);
        }
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
        where T6 : value struct
        where T7 : value struct
            inline static RTN VirtualCall(nint_t _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
            return (*(RTN(**)(void const*, T0, T1, T2, T3, T4, T5, T6, T7))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1, a2, a3, a4, a5, a6, a7);
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        inline static void Virtual_Call(nint_t _this, uintptr_t off) {
            return (*(void(**)(void const*))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer());
        }

        generic< typename T0>
        where T0 : value struct
            inline static void Virtual_Call(nint_t _this, uintptr_t off, T0 a0) {
            return (*(void(**)(void const*, T0))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0);
        }
        generic< typename T0, typename T1>
        where T0 : value struct
        where T1 : value struct
            inline static void Virtual_Call(nint_t _this, uintptr_t off, T0 a0, T1 a1) {
            return (*(void(**)(void const*, T0, T1))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1);
        }
        generic< typename T0, typename T1, typename T2>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
            inline static void Virtual_Call(nint_t _this, uintptr_t off, T0 a0, T1 a1, T2 a2) {
            return (*(void(**)(void const*, T0, T1, T2))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1, a2);
        }
        generic< typename T0, typename T1, typename T2, typename T3>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
            inline static void Virtual_Call(nint_t _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3) {
            return (*(void(**)(void const*, T0, T1, T2, T3))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1, a2, a3);
        }
        generic< typename T0, typename T1, typename T2, typename T3, typename T4>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
            inline static void Virtual_Call(nint_t _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
            return (*(void(**)(void const*, T0, T1, T2, T3, T4))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1, a2, a3, a4);
        }
        generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
            inline static void Virtual_Call(nint_t _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
            return (*(void(**)(void const*, T0, T1, T2, T3, T4, T5))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1, a2, a3, a4, a5);
        }
        generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
        where T6 : value struct
            inline static void Virtual_Call(nint_t _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
            return (*(void(**)(void const*, T0, T1, T2, T3, T4, T5, T6))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1, a2, a3, a4, a5, a6);
        }
        generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
        where T6 : value struct
        where T7 : value struct
            inline static void Virtual_Call(nint_t _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
            return (*(void(**)(void const*, T0, T1, T2, T3, T4, T5, T6, T7))(*(uintptr_t*)_this.ToPointer() + off))(_this.ToPointer(), a0, a1, a2, a3, a4, a5, a6, a7);
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        inline static nint_t const dAccess(nint_t ptr, uintptr_t off) {
            return nint_t((void*)(((uintptr_t)ptr.ToPointer()) + off));
        }

        inline static void const* dAccess(void const* ptr, uintptr_t off) {
            return (void const*)((void*)(((uintptr_t)ptr) + off));
        }

        generic<typename T> where T:value struct
            inline static T dAccess(void const* ptr, uintptr_t off) {
            return Unsafe::AsRef<T>(const_cast<void*>(reinterpret_cast<void*>(((uintptr_t)ptr) + off)));
        }
        
        generic<typename T> where T:value struct
            inline static T dAccess(nint_t ptr, uintptr_t off) {
            return Unsafe::AsRef<T>(const_cast<void*>(reinterpret_cast<void*>(((uintptr_t)ptr.ToPointer()) + off)));
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// <summary>
                    /// VirtualProtorype = Virtual Function Protorype Delegate
                    /// </summary>
        generic<typename VirtualProtorype>
        where VirtualProtorype : System::Delegate
            inline static VirtualProtorype VirtualFuction(nint_t _this, uintptr_t off) {
            return VirtualProtorype(Marshal::GetDelegateForFunctionPointer(nint_t((void*)(((*(uintptr_t*)_this.ToPointer()) + off))), VirtualProtorype::typeid));
        }


#undef SYM
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    /// <summary>
                    /// FunctionProtorype = Function Protorype Delegate
                    /// </summary>
        generic<typename FunctionProtorype>
        where FunctionProtorype : System::Delegate
            inline static FunctionProtorype SYM(System::String^ sym) {
            return FunctionProtorype(Marshal::GetDelegateForFunctionPointer<FunctionProtorype>(nint_t(::dlsym_real(marshalString(sym).c_str()))));
        }

        inline static nint_t SYM(System::String^ sym) {
            return nint_t(::dlsym_real(marshalString(sym).c_str()));
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#undef SymCall
        generic<typename RTN>
        where RTN : value struct
            inline static RTN SymCall(System::String^ sym) {
            return ((RTN(*)())(::dlsym_real(marshalString(sym).c_str())))();
        }

        generic<typename RTN, typename T0>
        where RTN : value struct
        where T0 : value struct
            inline static RTN SymCall(System::String^ sym, T0 a0) {
            return ((RTN(*)(T0))(::dlsym_real(marshalString(sym).c_str())))(a0);
        }

        generic<typename RTN, typename T0, typename T1>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
            inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1) {
            return ((RTN(*)(T0, T1))(::dlsym_real(marshalString(sym).c_str())))(a0, a1);
        }

        generic<typename RTN, typename T0, typename T1, typename T2>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
            inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1, T2 a2) {
            return ((RTN(*)(T0, T1, T2))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2);
        }

        generic<typename RTN, typename T0, typename T1, typename T2, typename T3>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
            inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3) {
            return ((RTN(*)(T0, T1, T2, T3))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3);
        }

        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
            inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
            return ((RTN(*)(T0, T1, T2, T3, T4))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4);
        }

        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
            inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
            return ((RTN(*)(T0, T1, T2, T3, T4, T5))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4, a5);
        }
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
        where T6 : value struct
            inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
            return ((RTN(*)(T0, T1, T2, T3, T4, T5, T6))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4, a5, a6);
        }
        generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        where RTN : value struct
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
        where T6 : value struct
        where T7 : value struct
            inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
            return ((RTN(*)(T0, T1, T2, T3, T4, T5, T6, T7))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4, a5, a6, a7);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        inline static void Sym_Call(System::String^ sym) {
            return ((void(*)())(::dlsym_real(marshalString(sym).c_str())))();
        }

        generic<typename T0>
        where T0 : value struct
            inline static void Sym_Call(System::String^ sym, T0 a0) {
            return ((void(*)(T0))(::dlsym_real(marshalString(sym).c_str())))(a0);
        }

        generic<typename T0, typename T1>
        where T0 : value struct
        where T1 : value struct
            inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1) {
            return ((void(*)(T0, T1))(::dlsym_real(marshalString(sym).c_str())))(a0, a1);
        }

        generic<typename T0, typename T1, typename T2>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
            inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1, T2 a2) {
            return ((void(*)(T0, T1, T2))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2);
        }

        generic<typename T0, typename T1, typename T2, typename T3>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
            inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3) {
            return ((void(*)(T0, T1, T2, T3))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3);
        }

        generic<typename T0, typename T1, typename T2, typename T3, typename T4>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
            inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
            return ((void(*)(T0, T1, T2, T3, T4))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4);
        }

        generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
            inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
            return ((void(*)(T0, T1, T2, T3, T4, T5))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4, a5);
        }
        generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
        where T6 : value struct
            inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
            return ((void(*)(T0, T1, T2, T3, T4, T5, T6))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4, a5, a6);
        }
        generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        where T0 : value struct
        where T1 : value struct
        where T2 : value struct
        where T3 : value struct
        where T4 : value struct
        where T5 : value struct
        where T6 : value struct
        where T7 : value struct
            inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
            return ((void(*)(T0, T1, T2, T3, T4, T5, T6, T7))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4, a5, a6, a7);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    };
}
