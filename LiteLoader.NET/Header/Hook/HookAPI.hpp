#pragma once
#include <HookAPI.h>
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <LiteLoader.NET/Header/Core/SecondaryRankPtr.hpp>

namespace LLNET {
	namespace Hook {
		using LLNET::Core::SecondaryRankPtr;

		public ref class HookAPI abstract
		{
		public:
			inline static int HookFunction(void* oldfunc, void** poutold, void* newfunc);
			inline static int HookFunction(System::IntPtr oldfunc, SecondaryRankPtr poutold, System::IntPtr newfunc);
			inline static void* dlsym_real(char const* name);
			inline static System::IntPtr dlsym_real(System::String^ name);
			inline static uintptr_t findSig(String^ szSignature);
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			generic<typename RTN>
			where RTN : System::ValueType
				inline static RTN VirtualCall(void const* _this, uintptr_t off) {
				return (*(RTN(**)(void const*))(*(uintptr_t*)_this + off))(_this);
			}

			generic<typename RTN, typename T0>
			where RTN : System::ValueType
			where T0 : System::ValueType
				inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0) {
				return (*(RTN(**)(void const*, T0))(*(uintptr_t*)_this + off))(_this, a0);
			}
			generic<typename RTN, typename T0, typename T1>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
				inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1) {
				return (*(RTN(**)(void const*, T0, T1))(*(uintptr_t*)_this + off))(_this, a0, a1);
			}
			generic<typename RTN, typename T0, typename T1, typename T2>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
				inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2) {
				return (*(RTN(**)(void const*, T0, T1, T2))(*(uintptr_t*)_this + off))(_this, a0, a1, a2);
			}
			generic<typename RTN, typename T0, typename T1, typename T2, typename T3>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
				inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3) {
				return (*(RTN(**)(void const*, T0, T1, T2, T3))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3);
			}
			generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
				inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
				return (*(RTN(**)(void const*, T0, T1, T2, T3, T4))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4);
			}
			generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
				inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
				return (*(RTN(**)(void const*, T0, T1, T2, T3, T4, T5))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4, a5);
			}
			generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
			where T6 : System::ValueType
				inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
				return (*(RTN(**)(void const*, T0, T1, T2, T3, T4, T5, T6))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4, a5, a6);
			}
			generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
			where T6 : System::ValueType
			where T7 : System::ValueType
				inline static RTN VirtualCall(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
				return (*(RTN(**)(void const*, T0, T1, T2, T3, T4, T5, T6, T7))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4, a5, a6, a7);
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			inline static void Virtual_Call(void const* _this, uintptr_t off) {
				return (*(void(**)(void const*))(*(uintptr_t*)_this + off))(_this);
			}

			generic< typename T0>
			where T0 : System::ValueType
				inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0) {
				return (*(void(**)(void const*, T0))(*(uintptr_t*)_this + off))(_this, a0);
			}
			generic< typename T0, typename T1>
			where T0 : System::ValueType
			where T1 : System::ValueType
				inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1) {
				return (*(void(**)(void const*, T0, T1))(*(uintptr_t*)_this + off))(_this, a0, a1);
			}
			generic< typename T0, typename T1, typename T2>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
				inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2) {
				return (*(void(**)(void const*, T0, T1, T2))(*(uintptr_t*)_this + off))(_this, a0, a1, a2);
			}
			generic< typename T0, typename T1, typename T2, typename T3>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
				inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3) {
				return (*(void(**)(void const*, T0, T1, T2, T3))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3);
			}
			generic< typename T0, typename T1, typename T2, typename T3, typename T4>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
				inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
				return (*(void(**)(void const*, T0, T1, T2, T3, T4))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4);
			}
			generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
				inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
				return (*(void(**)(void const*, T0, T1, T2, T3, T4, T5))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4, a5);
			}
			generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
			where T6 : System::ValueType
				inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
				return (*(void(**)(void const*, T0, T1, T2, T3, T4, T5, T6))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4, a5, a6);
			}
			generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
			where T6 : System::ValueType
			where T7 : System::ValueType
				inline static void Virtual_Call(void const* _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
				return (*(void(**)(void const*, T0, T1, T2, T3, T4, T5, T6, T7))(*(uintptr_t*)_this + off))(_this, a0, a1, a2, a3, a4, a5, a6, a7);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			generic<typename RTN>
			where RTN : System::ValueType
				inline static RTN VirtualCall(System::IntPtr _this, uintptr_t off) {
				return (*(RTN(**)(void const*))(*(uintptr_t*)(void*)_this + off))((void*)_this);
			}

			generic<typename RTN, typename T0>
			where RTN : System::ValueType
			where T0 : System::ValueType
				inline static RTN VirtualCall(System::IntPtr _this, uintptr_t off, T0 a0) {
				return (*(RTN(**)(void const*, T0))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0);
			}
			generic<typename RTN, typename T0, typename T1>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
				inline static RTN VirtualCall(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1) {
				return (*(RTN(**)(void const*, T0, T1))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1);
			}
			generic<typename RTN, typename T0, typename T1, typename T2>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
				inline static RTN VirtualCall(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1, T2 a2) {
				return (*(RTN(**)(void const*, T0, T1, T2))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1, a2);
			}
			generic<typename RTN, typename T0, typename T1, typename T2, typename T3>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
				inline static RTN VirtualCall(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3) {
				return (*(RTN(**)(void const*, T0, T1, T2, T3))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1, a2, a3);
			}
			generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
				inline static RTN VirtualCall(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
				return (*(RTN(**)(void const*, T0, T1, T2, T3, T4))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1, a2, a3, a4);
			}
			generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
				inline static RTN VirtualCall(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
				return (*(RTN(**)(void const*, T0, T1, T2, T3, T4, T5))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1, a2, a3, a4, a5);
			}
			generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
			where T6 : System::ValueType
				inline static RTN VirtualCall(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
				return (*(RTN(**)(void const*, T0, T1, T2, T3, T4, T5, T6))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1, a2, a3, a4, a5, a6);
			}
			generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
			where T6 : System::ValueType
			where T7 : System::ValueType
				inline static RTN VirtualCall(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
				return (*(RTN(**)(void const*, T0, T1, T2, T3, T4, T5, T6, T7))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1, a2, a3, a4, a5, a6, a7);
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			inline static void Virtual_Call(System::IntPtr _this, uintptr_t off) {
				return (*(void(**)(void const*))(*(uintptr_t*)(void*)_this + off))((void*)_this);
			}

			generic< typename T0>
			where T0 : System::ValueType
				inline static void Virtual_Call(System::IntPtr _this, uintptr_t off, T0 a0) {
				return (*(void(**)(void const*, T0))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0);
			}
			generic< typename T0, typename T1>
			where T0 : System::ValueType
			where T1 : System::ValueType
				inline static void Virtual_Call(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1) {
				return (*(void(**)(void const*, T0, T1))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1);
			}
			generic< typename T0, typename T1, typename T2>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
				inline static void Virtual_Call(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1, T2 a2) {
				return (*(void(**)(void const*, T0, T1, T2))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1, a2);
			}
			generic< typename T0, typename T1, typename T2, typename T3>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
				inline static void Virtual_Call(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3) {
				return (*(void(**)(void const*, T0, T1, T2, T3))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1, a2, a3);
			}
			generic< typename T0, typename T1, typename T2, typename T3, typename T4>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
				inline static void Virtual_Call(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
				return (*(void(**)(void const*, T0, T1, T2, T3, T4))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1, a2, a3, a4);
			}
			generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
				inline static void Virtual_Call(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
				return (*(void(**)(void const*, T0, T1, T2, T3, T4, T5))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1, a2, a3, a4, a5);
			}
			generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
			where T6 : System::ValueType
				inline static void Virtual_Call(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
				return (*(void(**)(void const*, T0, T1, T2, T3, T4, T5, T6))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1, a2, a3, a4, a5, a6);
			}
			generic< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
			where T6 : System::ValueType
			where T7 : System::ValueType
				inline static void Virtual_Call(System::IntPtr _this, uintptr_t off, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
				return (*(void(**)(void const*, T0, T1, T2, T3, T4, T5, T6, T7))(*(uintptr_t*)(void*)_this + off))((void*)_this, a0, a1, a2, a3, a4, a5, a6, a7);
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			inline static System::IntPtr const dAccess(System::IntPtr ptr, uintptr_t off) {
				return System::IntPtr((void*)(((uintptr_t)(void*)ptr) + off));
			}

			inline static void const* dAccess(void const* ptr, uintptr_t off) {
				return (void const*)((void*)(((uintptr_t)ptr) + off));
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						/// <summary>
						/// VirtualProtorype = Virtual Function Protorype Delegate
						/// </summary>
			generic<typename VirtualProtorype>
			where VirtualProtorype : System::Delegate
				inline static VirtualProtorype VirtualFuction(System::IntPtr _this, uintptr_t off) {
				return VirtualProtorype(Marshal::GetDelegateForFunctionPointer(System::IntPtr((void*)(((*(uintptr_t*)_this.ToPointer()) + off))), VirtualProtorype::typeid));
			}


#undef SYM
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						/// <summary>
						/// FunctionProtorype = Function Protorype Delegate
						/// </summary>
			generic<typename FunctionProtorype>
			where FunctionProtorype : System::Delegate
				inline static FunctionProtorype SYM(System::String^ sym) {
				return FunctionProtorype(Marshal::GetDelegateForFunctionPointer<FunctionProtorype>(System::IntPtr(::dlsym_real(marshalString(sym).c_str()))));
			}

			inline static System::IntPtr SYM(System::String^ sym) {
				return System::IntPtr(::dlsym_real(marshalString(sym).c_str()));
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#undef SymCall
			generic<typename RTN>
			where RTN : System::ValueType
				inline static RTN SymCall(System::String^ sym) {
				return ((RTN(*)())(::dlsym_real(marshalString(sym).c_str())))();
			}

			generic<typename RTN, typename T0>
			where RTN : System::ValueType
			where T0 : System::ValueType
				inline static RTN SymCall(System::String^ sym, T0 a0) {
				return ((RTN(*)(T0))(::dlsym_real(marshalString(sym).c_str())))(a0);
			}

			generic<typename RTN, typename T0, typename T1>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
				inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1) {
				return ((RTN(*)(T0, T1))(::dlsym_real(marshalString(sym).c_str())))(a0, a1);
			}

			generic<typename RTN, typename T0, typename T1, typename T2>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
				inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1, T2 a2) {
				return ((RTN(*)(T0, T1, T2))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2);
			}

			generic<typename RTN, typename T0, typename T1, typename T2, typename T3>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
				inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3) {
				return ((RTN(*)(T0, T1, T2, T3))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3);
			}

			generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
				inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
				return ((RTN(*)(T0, T1, T2, T3, T4))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4);
			}

			generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
				inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
				return ((RTN(*)(T0, T1, T2, T3, T4, T5))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4, a5);
			}
			generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
			where T6 : System::ValueType
				inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
				return ((RTN(*)(T0, T1, T2, T3, T4, T5, T6))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4, a5, a6);
			}
			generic<typename RTN, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
			where RTN : System::ValueType
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
			where T6 : System::ValueType
			where T7 : System::ValueType
				inline static RTN SymCall(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
				return ((RTN(*)(T0, T1, T2, T3, T4, T5, T6, T7))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4, a5, a6, a7);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			inline static void Sym_Call(System::String^ sym) {
				return ((void(*)())(::dlsym_real(marshalString(sym).c_str())))();
			}

			generic<typename T0>
			where T0 : System::ValueType
				inline static void Sym_Call(System::String^ sym, T0 a0) {
				return ((void(*)(T0))(::dlsym_real(marshalString(sym).c_str())))(a0);
			}

			generic<typename T0, typename T1>
			where T0 : System::ValueType
			where T1 : System::ValueType
				inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1) {
				return ((void(*)(T0, T1))(::dlsym_real(marshalString(sym).c_str())))(a0, a1);
			}

			generic<typename T0, typename T1, typename T2>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
				inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1, T2 a2) {
				return ((void(*)(T0, T1, T2))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2);
			}

			generic<typename T0, typename T1, typename T2, typename T3>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
				inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3) {
				return ((void(*)(T0, T1, T2, T3))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3);
			}

			generic<typename T0, typename T1, typename T2, typename T3, typename T4>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
				inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4) {
				return ((void(*)(T0, T1, T2, T3, T4))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4);
			}

			generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
				inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
				return ((void(*)(T0, T1, T2, T3, T4, T5))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4, a5);
			}
			generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
			where T6 : System::ValueType
				inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
				return ((void(*)(T0, T1, T2, T3, T4, T5, T6))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4, a5, a6);
			}
			generic<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
			where T0 : System::ValueType
			where T1 : System::ValueType
			where T2 : System::ValueType
			where T3 : System::ValueType
			where T4 : System::ValueType
			where T5 : System::ValueType
			where T6 : System::ValueType
			where T7 : System::ValueType
				inline static void Sym_Call(System::String^ sym, T0 a0, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7) {
				return ((void(*)(T0, T1, T2, T3, T4, T5, T6, T7))(::dlsym_real(marshalString(sym).c_str())))(a0, a1, a2, a3, a4, a5, a6, a7);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		};
	}
}
