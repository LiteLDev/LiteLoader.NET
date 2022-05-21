#pragma once

#include "ValueType.hpp"

namespace LLNET::RemoteCall
{
	public
	ref class RemoteCallAPI abstract
	{
	public:
		delegate Valuetype^ CallbackFn(List<Valuetype^>^);
		static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn);
		static bool ExportFunc(String^ nameSpace, String^ funcName, CallbackFn^ fn, IntPtr handler);

		static CallbackFn^ ImportFunc(String^ nameSpace, String^ funcName);

		static bool HasFunc(String^ nameSpace, String^ funcName);
		static bool RemoveFunc(String^ nameSpace, String^ funcName);
		static bool RemoveNameSpace(String^ nameSpace);
		static bool RemoveFuncs(List<Pair<String^, String^>>^ funcs);

		generic<typename TDelegate>
		where TDelegate:System::Delegate
			static bool ExportAs(String^ nameSpace, String^ funcName, TDelegate f)
		{
			return RemoteCallFunctionManager::_ExportAs<TDelegate>(nameSpace, funcName, f);
		}
	internal:
		ref class RemoteCallFunctionManager sealed {
		public:
			generic<typename TDelegate>
			where TDelegate : System::Delegate
				static bool _ExportAs(String^ nameSpace, String^ funcName, TDelegate f)
			{
				auto func = gcnew Function(nameSpace, funcName, f);
				auto ret = ExportFunc(nameSpace, funcName, gcnew CallbackFn(func, &Function::Invoke));
				if (ret)
				{
					RemoteCallFunction->Add(func);
				}
				return ret;
			}
		private:
			ref class Function {
			public:
				Function(String^ nameSpace, String^ funcName, System::Delegate^ f)
					:NameSpace(nameSpace), FuncName(funcName), delfunc(f)
				{
				}

				String^ NameSpace;
				String^ FuncName;
				System::Delegate^ delfunc;
			public:
				Valuetype^ Invoke(List<Valuetype^>^ args) {
					throw gcnew System::NotImplementedException;
				}
			};
		private:
			static bool IsElementType(System::Type^ type) {
				for each (auto var in Simple_ElementType) {
					if (type == var)
						return true;
				}
				return false;
			}
			static List<Function^>^ RemoteCallFunction = gcnew List<Function^>;
			static array<System::Type^>^ Simple_ElementType = gcnew array<System::Type^>
			{
				void::typeid,
					bool::typeid,
					String::typeid,
					NumberType::typeid,
					MC::Player::typeid,
					MC::Actor::typeid,
					MC::BlockActor::typeid,
					MC::Container::typeid,
					MC::Vec3::typeid,
					MC::BlockPos::typeid,
					ItemType::typeid,
					BlockType::typeid,
					NbtType::typeid
			};
		};

	public:
		//防止gc回收
		static Dictionary<uint64_t, NativeCallbackHandler^>^ CallbackData = gcnew Dictionary<uint64_t, NativeCallbackHandler^>;

	private:
		ref class RemoteCallHelper
		{
		private:
			::RemoteCall::CallbackFn const* pFunc;
			Valuetype^ Invoke(List<Valuetype^>^ list) {
				NULL_ARG_CHEEK(list);

				auto count = (size_t)list->Count;
				std::vector<::RemoteCall::ValueType> stdvector;
				for (auto i = 0; i < count; ++i)
				{
					stdvector.emplace_back(*list[i]->NativePtr);
				}
				auto& ret = (*pFunc)(stdvector);
				return gcnew Valuetype(ret);
			};
			RemoteCallHelper(::RemoteCall::CallbackFn const& p)
				: pFunc(new ::RemoteCall::CallbackFn(std::move(p)))
			{
			}
			~RemoteCallHelper() {
				delete pFunc;
			}

		public:
			static Pair<RemoteCallHelper^, CallbackFn^> Create(::RemoteCall::CallbackFn const& p) {
				auto instance = gcnew RemoteCallHelper(p);
				return Pair< RemoteCallHelper^, CallbackFn^>(instance, gcnew CallbackFn(instance, &RemoteCallHelper::Invoke));
			}
		};

	};
} // namespace LLNET::RemoteCall
