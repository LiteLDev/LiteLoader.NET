#pragma once
#include <AllowListAPI.h>
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>

namespace LiteLoader::AllowList
{
    /// <summary> 
    /// For managing AllowList
    /// <example>
    /// <para>[Usage]</para>
    /// <para>　AllowListManager().has("steve"[, "114514"]);</para>
    /// <para>　AllowListManager().add("alex"[, "11451419", true]).reload();</para>
    /// <para>　AllowListManager().remove("mojang"[, "233333"]).reload();</para>
    /// <para>　AllowListManager().add(...).remove(...).reload();</para>
    /// <para>[Note]</para>
    /// <para>　If you don't call reload after add/remove, the changes will only write to file
    /// but it will not take effect in the game.
    /// This means the player you added won't be able to join the game until reloading</para>
    /// </example> 
    /// </summary>
    public ref class AllowListManager
    {
    private:
        ::AllowListManager* _this;

    public:
        AllowListManager()
        {
            _this = new ::AllowListManager();
        }
        !AllowListManager()
        {
            delete _this;
        }
        ~AllowListManager()
        {
            this->!AllowListManager();
            GC::SuppressFinalize(this);
        }

        property System::String^ AllowList {
            System::String^ get() 
            {
                return marshalString(_this->allowList.dump());
            };

            void set(System::String^ str)
            {
                _this->allowList = nlohmann::json::parse(marshalString(str));
            };
        };
        property size_t Size
        {
            size_t get()
            {
                return _this->size();
            }
        }
        bool Has(System::String^ name)
        {
            return Has(name, "");
        }
        bool Has(System::String^ name, System::String^ xuid)
        {
            return _this->has(marshalString(name), marshalString(xuid));
        }
        bool Has(System::String^ name, System::String^ xuid, [Out] size_t% index)
        {
            pin_ptr<size_t> p = &index;
            return _this->has(marshalString(name), marshalString(xuid), *p);
        }
        AllowListManager^ Add(System::String^ name) {
            return Add(name, "");
        };
        AllowListManager^ Add(System::String^ name, System::String^ xuid) {
            return Add(name, xuid, false);
        };
        AllowListManager^ Add(System::String^ name, System::String^ xuid, bool ignore) {
            _this->add(marshalString(name), marshalString(xuid), ignore);
            return this;
        };
        AllowListManager^ Remove(System::String^ name) {
            return Remove(name, "");
        };
        AllowListManager^ Remove(System::String^ name, System::String^ xuid) {
            _this->remove(marshalString(name), marshalString(xuid));
            return this;
        };
        void Reload()
        {
            _this->reload();
        }
    };
} // namespace LiteLoader::AllowList
