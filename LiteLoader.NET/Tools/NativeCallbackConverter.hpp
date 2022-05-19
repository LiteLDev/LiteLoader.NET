#include <Utils/Hash.h>
#include "../Main/Global.hpp"
#pragma once

constexpr size_t do_hash()
{
    return 0;
}

using CHash = size_t;

public
interface class NativeCallbackHandler : System::IDisposable
{
};

/**
 * .Net-Native回调转换工具
 *
 * class_name          : 类名   方便调用
 * callback_delegate   : .Net委托类型
 * ret                 : Native回调函数返回类型
 * ...                 : Native回调函数参数列表
 *
 * ====================API======================
 *
 * class_name::Create(dlegate^ callback) :返回包含Native函数指针与转换器实例的Pair
 * class_name:
 *    GCHandle gch:防止回收.Net回调委托的handle
 *    callback_delegate^ delfunc:.Net回调委托
 *
 * Ps:
 * 稳定性未知，且转换器实例的回收会导致.Net委托实例的释放与Native函数指针的失效
 * 等待稳定性测试.jpg
 */
#define DelegateToNativeHelper(class_name, callback_delegate, ret, ...)                                                                             \
                                                                                                                                                    \
    template <CHash, CHash>                                                                                                                         \
    ref class NativeCallbackTemplate;                                                                                                               \
                                                                                                                                                    \
    template <>                                                                                                                                     \
    ref class NativeCallbackTemplate<do_hash(#class_name) ^ do_hash(#ret), do_hash(#callback_delegate) ^ do_hash(#__VA_ARGS__)>                     \
        : public NativeCallbackHandler                                                                                                              \
    {                                                                                                                                               \
    public:                                                                                                                                         \
        typedef ret (*pCallback)(__VA_ARGS__);                                                                                                      \
        delegate ret delCallback(__VA_ARGS__);                                                                                                      \
                                                                                                                                                    \
    public:                                                                                                                                         \
        GCHandle gch;                                                                                                                               \
        callback_delegate ^ delfunc;                                                                                                                \
                                                                                                                                                    \
    public:                                                                                                                                         \
        value class __Pair                                                                                                                          \
        {                                                                                                                                           \
        public:                                                                                                                                     \
            pCallback pCallbackFn;                                                                                                                  \
            NativeCallbackTemplate ^ converter;                                                                                                     \
            __Pair(pCallback p, NativeCallbackTemplate ^ obj)                                                                                       \
                : pCallbackFn(p)                                                                                                                    \
                , converter(obj)                                                                                                                    \
            {                                                                                                                                       \
            }                                                                                                                                       \
        };                                                                                                                                          \
                                                                                                                                                    \
    protected:                                                                                                                                      \
        NativeCallbackTemplate()                                                                                                                    \
            : delfunc(nullptr)                                                                                                                      \
        {                                                                                                                                           \
        }                                                                                                                                           \
        NativeCallbackTemplate(callback_delegate ^ callback)                                                                                        \
            : delfunc(callback)                                                                                                                     \
        {                                                                                                                                           \
        }                                                                                                                                           \
        ~NativeCallbackTemplate()                                                                                                                   \
        {                                                                                                                                           \
            this->!NativeCallbackTemplate();                                                                                                        \
            GC::SuppressFinalize(this);                                                                                                             \
        }                                                                                                                                           \
        !NativeCallbackTemplate()                                                                                                                   \
        {                                                                                                                                           \
            if (gch.IsAllocated)                                                                                                                    \
                gch.Free();                                                                                                                         \
        }                                                                                                                                           \
                                                                                                                                                    \
    private:                                                                                                                                        \
        ret NATIVECALLBACK NativeCallbackFunc(__VA_ARGS__);                                                                                         \
                                                                                                                                                    \
    public:                                                                                                                                         \
        static __Pair Create(callback_delegate ^ callback)                                                                                          \
        {                                                                                                                                           \
            auto instance = gcnew NativeCallbackTemplate(callback);                                                                                 \
            delCallback ^ del = gcnew delCallback(instance, &NativeCallbackFunc);                                                                   \
            instance->gch = GCHandle::Alloc(del);                                                                                                   \
            auto p = static_cast<pCallback>((void*)Marshal::GetFunctionPointerForDelegate(del));                                                    \
            return __Pair(p, instance);                                                                                                             \
        }                                                                                                                                           \
    };                                                                                                                                              \
                                                                                                                                                    \
    ref class class_name : public NativeCallbackTemplate<do_hash(#class_name) ^ do_hash(#ret), do_hash(#callback_delegate) ^ do_hash(#__VA_ARGS__)> \
    {                                                                                                                                               \
    };                                                                                                                                              \
                                                                                                                                                    \
    ret NativeCallbackTemplate<do_hash(#class_name) ^ do_hash(#ret), do_hash(#callback_delegate) ^ do_hash(#__VA_ARGS__)>::NativeCallbackFunc(__VA_ARGS__)