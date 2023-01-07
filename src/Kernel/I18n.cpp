#include <src/Header/I18n.hpp>

namespace LiteLoader::I18N
{
    I18nBase::_LangData^ I18nBase::LangData::get()
    {
        auto ret = gcnew _LangData(static_cast<int>(nativePtr->langData.size()));

        for (auto& [k, umap] : nativePtr->langData)
        {
            auto subLangData = gcnew _SubLangData(static_cast<int>(umap.size()));

            for (auto& [_k, v] : umap)
            {
                subLangData->Add(marshalString(_k), marshalString(v));
            }

            ret->Add(marshalString(k), subLangData);
        }

        return ret;
    }

    I18nBase::_LangData^ I18nBase::DefaultLangData::get()
    {
        auto ret = gcnew _LangData(static_cast<int>(nativePtr->langData.size()));

        for (auto& [k, umap] : nativePtr->defaultLangData)
        {
            auto subLangData = gcnew _SubLangData(static_cast<int>(umap.size()));

            for (auto& [_k, v] : umap)
            {
                subLangData->Add(marshalString(_k), marshalString(v));
            }

            ret->Add(marshalString(k), subLangData);
        }

        return ret;
    }

    void I18nBase::LangData::set(_LangData^ value)
    {
        ::I18nBase::LangData data;

        for each (auto kv in value)
        {
            ::I18nBase::SubLangData subData;

            for each (auto _kv in kv.Value)
            {
                subData.insert(std::make_pair(marshalString(_kv.Key), marshalString(_kv.Value)));
            }

            data.insert(std::make_pair(marshalString(kv.Key), std::move(subData)));
        }

        nativePtr->langData = std::move(data);
    }

    void I18nBase::DefaultLangData::set(_LangData^ value)
    {
        ::I18nBase::LangData data;

        for each (auto kv in value)
        {
            ::I18nBase::SubLangData subData;

            for each (auto _kv in kv.Value)
            {
                subData.insert(std::make_pair(marshalString(_kv.Key), marshalString(_kv.Value)));
            }

            data.insert(std::make_pair(marshalString(kv.Key), std::move(subData)));
        }

        nativePtr->defaultLangData = std::move(data);
    }

    inline String^ I18nBase::Get(String^ key, String^ localeName)
    {
        return marshalString(nativePtr->get(marshalString(key), marshalString(localeName)));
    }

    inline String^ I18nBase::Get(String^ key)
    {
        return Get(key, String::Empty);
    }

    inline String^ I18nBase::GetDefaultLocaleName()
    {
        return marshalString(NativePtr->getDefaultLocaleName());
    }

    //inline I18nBase^ I18nBase::Clone()
    //{
    //    return gcnew I18nBase()
    //}




    inline SingleFileI18N::SingleFileI18N()
        :I18nBase((void*)nullptr)
    {
        nativePtr = new ::SingleFileI18N();
        ownsNativeInstance = true;
    }

    inline SingleFileI18N::SingleFileI18N(String^ filePath, String^ defaultLocaleName, _LangData^ defaultLangData)
        :I18nBase((void*)nullptr)
    {
        ::I18nBase::LangData data;

        for each (auto kv in defaultLangData)
        {
            ::I18nBase::SubLangData subData;

            for each (auto _kv in kv.Value)
            {
                subData.insert(std::make_pair(marshalString(_kv.Key), marshalString(_kv.Value)));
            }

            data.insert(std::make_pair(marshalString(kv.Key), std::move(subData)));
        }

        nativePtr = new ::SingleFileI18N(marshalString(filePath), marshalString(defaultLocaleName), data);
        ownsNativeInstance = true;
    }

    inline SingleFileI18N::SingleFileI18N(String^ filePath, String^ defaultLocaleName)
        :I18nBase((void*)nullptr)
    {
        nativePtr = new ::SingleFileI18N(marshalString(filePath), marshalString(defaultLocaleName));
        ownsNativeInstance = true;
    }

    inline SingleFileI18N::SingleFileI18N(String^ filePath)
        :I18nBase((void*)nullptr)
    {
        nativePtr = new ::SingleFileI18N(marshalString(filePath));
        ownsNativeInstance = true;
    }

    inline SingleFileI18N::SingleFileI18N(SingleFileI18N% other)
        :I18nBase((void*)nullptr)
    {
        nativePtr = new ::SingleFileI18N(*static_cast<::SingleFileI18N*>(other.nativePtr));
        ownsNativeInstance = true;
    }

    inline void SingleFileI18N::Load(String^ dirName)
    {
        static_cast<::SingleFileI18N*>(nativePtr)->load(marshalString(dirName));
    }

    inline void SingleFileI18N::Save()
    {
        static_cast<::SingleFileI18N*>(nativePtr)->save();
    }

    inline I18nBase::I18nClassType SingleFileI18N::GetI18nType()
    {
        return I18nClassType::SingleFile;
    }



    inline MultiFileI18N::MultiFileI18N()
        :I18nBase((void*)nullptr)
    {
        nativePtr = new ::MultiFileI18N();
        ownsNativeInstance = true;
    }

    inline MultiFileI18N::MultiFileI18N(String^ filePath, String^ defaultLocaleName, _LangData^ defaultLangData)
        :I18nBase((void*)nullptr)
    {
        ::I18nBase::LangData data;

        for each (auto kv in defaultLangData)
        {
            ::I18nBase::SubLangData subData;

            for each (auto _kv in kv.Value)
            {
                subData.insert(std::make_pair(marshalString(_kv.Key), marshalString(_kv.Value)));
            }

            data.insert(std::make_pair(marshalString(kv.Key), std::move(subData)));
        }

        nativePtr = new ::MultiFileI18N(marshalString(filePath), marshalString(defaultLocaleName), data);
        ownsNativeInstance = true;
    }

    inline MultiFileI18N::MultiFileI18N(String^ filePath, String^ defaultLocaleName)
        :I18nBase((void*)nullptr)
    {
        nativePtr = new ::MultiFileI18N(marshalString(filePath), marshalString(defaultLocaleName));
        ownsNativeInstance = true;
    }

    inline MultiFileI18N::MultiFileI18N(String^ filePath)
        :I18nBase((void*)nullptr)
    {
        nativePtr = new ::MultiFileI18N(marshalString(filePath));
        ownsNativeInstance = true;
    }

    inline MultiFileI18N::MultiFileI18N(MultiFileI18N% other)
        :I18nBase((void*)nullptr)
    {
        nativePtr = new ::MultiFileI18N(*static_cast<::MultiFileI18N*>(other.nativePtr));
        ownsNativeInstance = true;
    }

    inline void MultiFileI18N::Load(String^ dirName)
    {
        static_cast<::MultiFileI18N*>(nativePtr)->load(marshalString(dirName));
    }

    inline void MultiFileI18N::Save(bool nested)
    {
        static_cast<::MultiFileI18N*>(nativePtr)->save(nested);
    }

    inline void MultiFileI18N::Save()
    {
        static_cast<::MultiFileI18N*>(nativePtr)->save();
    }

    inline I18nBase::I18nClassType MultiFileI18N::GetI18nType()
    {
        return I18nClassType::MultiFile;
    }
}