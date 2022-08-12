#pragma unmanaged
#include <I18nAPI.h>

std::string I18N::get(const std::string& key, const std::string& langCode) {
    auto& langc = (langCode.empty() ? defaultLocaleName : langCode);
    auto langType = langc.substr(0, 2);
    if (langData.count(langc)) { // If there is lang data for the language
        auto& lang = langData[langc];
        if (lang.count(key)) { // If there is matched key in the language data
            return lang[key];
        }
    }
    // Search for the similar language in langData
    for (auto& [lc, ld] : langData) {
        if (lc.length() < 2) {
            continue;
        }
        if (lc.substr(0, 2) == langType) {
            if (ld.count(key)) {
                return ld[key];
            }
        }
    }
    if (!defaultLangData.empty()) {
        // If not found, try falling back to the default language data
        if (defaultLangData.count(langc)) {
            auto& lang = defaultLangData[langc];
            if (lang.count(key)) {
                return lang[key]; // Fall back
            }
        }
        // Search for the similar language
        for (auto& [lc, ld] : defaultLangData) {
            if (lc.length() < 2) {
                continue;
            }
            if (lc.substr(0, 2) == langType) {
                if (ld.count(key)) {
                    return ld[key];
                }
            }
        }
    }
    // Finally, not found, return the key
    return key;
}

I18N* I18N::clone() {
    if (getType() == Type::SingleFile) {
        return new SingleFileI18N(*(SingleFileI18N*)this);
    }
    else if (getType() == Type::MultiFile) {
        return new MultiFileI18N(*(MultiFileI18N*)this);
    }
    return nullptr;
}

std::string I18N::getDefaultLocaleName() {
    return this->defaultLocaleName;
}