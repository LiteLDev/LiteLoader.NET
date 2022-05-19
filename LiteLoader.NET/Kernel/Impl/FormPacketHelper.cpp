#include "../../Header/Impl/FormPacketHelper.h"

namespace LLNET::Helper
{
unsigned int FormPacketHelper::NewFormId()
{
    return ::NewFormId();
}

DelegateToNativeHelper(SimpleFormPacketCallback, FormPacketHelper::SimpleFormPacketCallbackHandler, void, ::Player* pl, int a1)
{
    auto player = gcnew MC::Player(pl);
    try
    {
        delfunc(player, a1);
    }
    catch (System::Exception ^ ex)
    {
        System::Console::WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, ex->GetType()->ToString());
        System::Console::WriteLine(ex->Message);
    }
    delete player;
}

void FormPacketHelper::SetSimpleFormPacketCallback(unsigned formId, SimpleFormPacketCallbackHandler ^ callback)
{
    auto % pair = SimpleFormPacketCallback::Create(callback);
    auto pfunc = pair.pCallbackFn;
    ::SetSimpleFormPacketCallback(formId, pfunc);
    GC::KeepAlive(pair.converter);
}

DelegateToNativeHelper(ModalFormPacketCallback, FormPacketHelper::ModalFormPacketCallbackHandler, void, ::Player* pl, bool a1)
{
    auto player = gcnew MC::Player(pl);
    try
    {
        delfunc(player, a1);
    }
    catch (System::Exception ^ ex)
    {
        System::Console::WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, ex->GetType()->ToString());
        System::Console::WriteLine(ex->Message);
    }
    delete player;
}

void FormPacketHelper::SetModalFormPacketCallback(unsigned formId, ModalFormPacketCallbackHandler ^ callback)
{
    auto % pair = ModalFormPacketCallback::Create(callback);
    auto pfunc = pair.pCallbackFn;
    ::SetModalFormPacketCallback(formId, pfunc);
    GC::KeepAlive(pair.converter);
}

DelegateToNativeHelper(CustomFormPacketCallback, FormPacketHelper::CustomFormPacketCallbackHandler, void, ::Player* pl, std::string a1)
{
    auto player = gcnew MC::Player(pl);
    try
    {
        delfunc(player, marshalString(a1));
    }
    catch (System::Exception ^ ex)
    {
        System::Console::WriteLine(LLNET_DEFAULT_EXCEPTION_MESSAGE, ex->GetType()->ToString());
        System::Console::WriteLine(ex->Message);
    }
    delete player;
}

void FormPacketHelper::SetCustomFormPacketCallback(unsigned formId, CustomFormPacketCallbackHandler ^ callback)
{
    auto % pair = CustomFormPacketCallback::Create(callback);
    auto pfunc = pair.pCallbackFn; 
    ::SetCustomFormPacketCallback(formId, pfunc);
    GC::KeepAlive(pair.converter);
}

void FormPacketHelper::SetSimpleFormBuilderData(unsigned formId, Form::SimpleForm ^ data)
{
    throw gcnew System::NotImplementedException();
}

void FormPacketHelper::SetCustomFormBuilderData(unsigned formId, Form::CustomForm ^ data)
{
    throw gcnew System::NotImplementedException();
}

void FormPacketHelper::HandleFormPacket(MC::Player ^ player, unsigned formId, String^ data)
{
    throw gcnew System::NotImplementedException();
}


} // namespace LLNET::Helper
