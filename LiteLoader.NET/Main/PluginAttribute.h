namespace LLNET
{
public
ref class PluginLoadModeAttribute : public System::Attribute
{
public:
    enum class LoadMode
    {
        CLRRuntimeHost,
        Default,
        Auto
    };

public:
    PluginLoadModeAttribute(LoadMode m)
        : mode(m)
    {
    }
    property LoadMode Mode
    {
        LoadMode get()
        {
            return mode;
        }
    }

private:
    LoadMode mode;
};
} // namespace LLNET