#pragma once
#include <llapi/I18nAPI.h>

#include <LiteLoader.NET/Main/ClassTemplate.hpp>
#include <LiteLoader.NET/Tools/PropertryHelper.hpp>

namespace LiteLoader::I18N
{
    public ref class I18nBase abstract : ClassTemplate<I18nBase, ::I18nBase>
    {
    internal:
        ::I18nBase* _this = nativePtr;

    public:
        __ctor(I18nBase, ::I18nBase);

        using _SubLangData = Dictionary<String^, String^>;
        using _LangData = Dictionary<String^, _SubLangData^>;

    public:
        enum class I18nClassType :char
        {
            None,
            SingleFile,
            MultiFile,
            Custom,
        };

    public:
        Property_Enum(I18nClassType, ::I18nBase::Type, type, I18nType);

        property _LangData^ LangData
        {
            _LangData^ get();
            void set(_LangData^ value);
        }

        property _LangData^ DefaultLangData
        {
            _LangData^ get();
            void set(_LangData^ value);
        }

        Property_String(defaultLocaleName, DefaultLocaleName);

    public:
        virtual String^ Get(String^ key, String^ localeName);
        virtual String^ Get(String^ key);

        virtual I18nClassType GetI18nType() abstract;

        virtual String^ GetDefaultLocaleName();

        //virtual I18nBase^ Clone();

    public:
        literal String^ POD_KEY = "ll_plugin_i18n";
    };



    public ref class SingleFileI18N : I18nBase
    {
    internal:
        ::SingleFileI18N* _this = static_cast<::SingleFileI18N*>(nativePtr);

    public:
        __ctor_base(SingleFileI18N, ::SingleFileI18N, I18nBase);

    public:
        SingleFileI18N();

        SingleFileI18N(String^ filePath, String^ defaultLocaleName, _LangData^ defaultLangData);
        SingleFileI18N(String^ filePath, String^ defaultLocaleName);
        SingleFileI18N(String^ filePath);

        SingleFileI18N(SingleFileI18N% other);

    public:
        Property_String(filePath, FilePath);

    public:
        void Load(String^ dirName);
        void Save();

        virtual I18nClassType GetI18nType() override;
    };

    public ref class MultiFileI18N : I18nBase
    {
    internal:
        ::MultiFileI18N* _this = static_cast<::MultiFileI18N*>(nativePtr);

    public:
        __ctor_base(MultiFileI18N, ::MultiFileI18N, I18nBase);

    public:
        MultiFileI18N();

        MultiFileI18N(String^ filePath, String^ defaultLocaleName, _LangData^ defaultLangData);
        MultiFileI18N(String^ filePath, String^ defaultLocaleName);
        MultiFileI18N(String^ filePath);

        MultiFileI18N(MultiFileI18N% other);

    public:
        Property_String(dirPath, DirPath);

    public:
        void Load(String^ dirName);
        void Save(bool nested);
        void Save();

        virtual I18nClassType GetI18nType() override;
    };

    public ref class Translation __static
    {

    };
}