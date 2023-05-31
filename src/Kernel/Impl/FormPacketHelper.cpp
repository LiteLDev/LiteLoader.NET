#include <src/Header/Impl/FormPacketHelper.hpp>

namespace LiteLoader::Helper
{
unsigned int FormPacketHelper::NewFormId()
{
    return ::NewFormId();
}

DelegateToNativeHelper(SimpleFormPacketCallback, FormPacketHelper::SimpleFormPacketCallbackHandler, void, ::Player* pl, int a1)
{
    auto player = gcnew MC::Player(pl);
    delfunc(player, a1);
}

void FormPacketHelper::SetSimpleFormPacketCallback(unsigned formId, SimpleFormPacketCallbackHandler ^ callback)
{
    auto % pair = SimpleFormPacketCallback::Create(callback);
    auto pfunc = pair.pCallbackFn;
    ::SetSimpleFormPacketCallback(formId, pfunc);
    GCHandle::Alloc(pair.converter);
}

DelegateToNativeHelper(ModalFormPacketCallback, FormPacketHelper::ModalFormPacketCallbackHandler, void, ::Player* pl, bool a1)
{
    auto player = gcnew MC::Player(pl);
    delfunc(player, a1);
}

void FormPacketHelper::SetModalFormPacketCallback(unsigned formId, ModalFormPacketCallbackHandler ^ callback)
{
    auto % pair = ModalFormPacketCallback::Create(callback);
    auto pfunc = pair.pCallbackFn;
    ::SetModalFormPacketCallback(formId, pfunc);
    GCHandle::Alloc(pair.converter);
}

DelegateToNativeHelper(CustomFormPacketCallback, FormPacketHelper::CustomFormPacketCallbackHandler, void, ::Player* pl, std::string a1)
{
    auto player = gcnew MC::Player(pl);
    delfunc(player, marshalString(a1));
}

void FormPacketHelper::SetCustomFormPacketCallback(unsigned formId, CustomFormPacketCallbackHandler ^ callback)
{
    auto % pair = CustomFormPacketCallback::Create(callback);
    auto pfunc = pair.pCallbackFn; 
    ::SetCustomFormPacketCallback(formId, pfunc);
    GCHandle::Alloc(pair.converter);
}

/*void FormPacketHelper::SetSimpleFormBuilderData(unsigned formId, Form::SimpleForm^ data)
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
}*/


} // namespace LiteLoader::Helper
