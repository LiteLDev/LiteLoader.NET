#pragma once
#pragma region Property

#define Property(type, nativeName, name)            \
    property type name                              \
    {                                               \
        inline type get()                           \
        {                                           \
            return this->NativePtr->nativeName;     \
        }                                           \
        inline void set(type arg)                   \
        {                                           \
            this->NativePtr->nativeName = arg;      \
        }                                           \
    }

#define Property_Instance(Namespace, type, nativeName, name)            \
    property Namespace::type ^ name {                                   \
        inline Namespace::type ^ get() {                                \
            return gcnew Namespace::type(this->NativePtr->nativeName);  \
        } inline void                                                   \
            set(Namespace::type ^ arg)                                  \
        {                                                               \
            this->NativePtr->nativeName = arg;                          \
        }                                                               \
    }

#define Property_ValueType(Namespace, type, nativeName, name)           \
    property Namespace::type name {                                     \
        inline Namespace::type get() {                                  \
            return Namespace::type(this->NativePtr->nativeName);        \
        } inline void                                                   \
            set(Namespace::type arg)                                    \
        {                                                               \
            this->NativePtr->nativeName = arg;                          \
        }                                                               \
    }

#define Property_Ptr(Namespace, type, nativeName, name)                 \
    property Namespace::type ^ name {                                   \
        inline Namespace::type ^ get() {                                \
            return gcnew Namespace::type(this->NativePtr->nativeName);  \
        } inline void                                                   \
            set(Namespace::type ^ arg)                                  \
        {                                                               \
            this->NativePtr->nativeName = arg->NativePtr;               \
        }                                                               \
    }

#define Property_Enum(type, nativeEnum, nativeName, name)       \
    property type name                                          \
    {                                                           \
        inline type get()                                       \
        {                                                       \
            return ((type)(this->NativePtr->nativeName));       \
        }                                                       \
        inline void set(type arg)                               \
        {                                                       \
            this->NativePtr->nativeName = ((nativeEnum)(arg));  \
        }                                                       \
    }

#define Property_String(nativeName, name)                                           \
    property String^ name {                                                         \
        inline String^ get() {                                                      \
            return marshalString(this->NativePtr->nativeName);    \
        } inline void                                                               \
            set(String^ arg)                                                        \
        {                                                                           \
            this->NativePtr->nativeName = marshalString(arg);     \
        }                                                                           \
    }

#define Property_ReadOnly(type, nativeName, name)   \
    property type name                              \
    {                                               \
        inline type get()                           \
        {                                           \
            return this->NativePtr->nativeName;     \
        }                                           \
    }

#define Property_Instance_ReadOnly(Namespace, type, nativeName, name)   \
    property Namespace::type ^ name {                                   \
        inline Namespace::type ^ get() {                                \
            return gcnew Namespace::type(this->NativePtr->nativeName);  \
        }                                                               \
    }

#define Property_Ptr_ReadOnly(Namespace, type, nativeName, name)                \
    property Namespace::type ^ name {                                           \
        inline Namespace::type ^ get() {                                        \
            return gcnew Namespace::type((void*)this->NativePtr->nativeName);   \
        }                                                                       \
    }

#define Property_Enum_ReadOnly(type, nativeEnum, nativeName, name)  \
    property type name                                              \
    {                                                               \
        inline type get()                                           \
        {                                                           \
            return ((type)(this->NativePtr->nativeName));           \
        }                                                           \
    }

#define Property_String_ReadOnly(nativeName, name)              \
    property String^ name {                                     \
        inline String^ get() {                                  \
            return toSysString(this->NativePtr->nativeName);    \
        }                                                       \
    }

#pragma endregion
