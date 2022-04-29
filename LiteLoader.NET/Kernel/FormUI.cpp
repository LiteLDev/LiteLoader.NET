#include "../Header/FormUI.hpp"

namespace LLNET::Form
{
inline Button::Button(System::String ^ text, System::String ^ image, ButtonCallback ^ callback)
    : text(text)
    , image(image)
    , callback(callback)
{
}

inline Button::Button(System::String ^ text, System::String ^ image)
    : text(text)
    , image(image)
    , callback(nullptr)
{
}

inline Button::Button(System::String ^ text)
    : text(text)
    , image("")
    , callback(nullptr)
{
}

inline Button::~Button()
{
    if (gch.IsAllocated)
    {
        gch.Free();
    }
}

inline void Button::SetText(System::String ^ _text)
{
    this->text = _text;
}
inline void Button::SetImage(System::String ^ _image)
{
    this->image = _image;
}
inline void Button::SetCallback(ButtonCallback ^ _callback)
{
    this->callback = _callback;
}

void NATIVECALLBACK Button::callbackfunc(::Player* p)
{
    try
    {
        callback(gcnew MC::Player(p));
    }
    CATCH
}

Button::NativeCallback Button::ToNativeCallback()
{
    if (callback == nullptr)
        return NativeCallback();
    auto de_callback = gcnew _ButtonCallback(this, &Button::callbackfunc);
    gch = GCHandle::Alloc(de_callback);
    auto pfunc = static_cast<NativeCallback>(
        Marshal::GetFunctionPointerForDelegate(de_callback).ToPointer());
    return pfunc;
}

inline void CustomFormElement::SetName(System::String ^ _name)
{
    this->name = _name;
}

inline System::String ^ CustomFormElement::GetString()
{
    return this->value;
}

inline int CustomFormElement::GetNumber()
{
    return System::Convert::ToInt32(value);
}

bool CustomFormElement::GetBool()
{
    if (System::String::IsNullOrEmpty(value) || value == "0" || value == "false" || value == "False" || value == "FALSE")
        return false;
    return true;
}


inline Label::Label(System::String ^ name, System::String ^ text)
    : text(text)
{
    SetName(name);
}

inline Label::Type Label::GetType()
{
    return Type::Label;
}

inline void Label::SetText(System::String ^ _text)
{
    this->text = _text;
}


inline Input::Input(System::String ^ name, System::String ^ title, System::String ^ placeholder, System::String ^ def)
    : title(title)
    , placeholder(placeholder)
    , def(def)
{
    SetName(name);
}

inline Input::Input(System::String ^ name, System::String ^ title, System::String ^ placeholder)
    : title(title)
    , placeholder(placeholder)
    , def("")
{
    SetName(name);
}

inline Input::Input(System::String ^ name, System::String ^ title)
    : title(title)
    , placeholder("")
    , def("")
{
    SetName(name);
}

inline Input::Type Input::GetType()
{
    return Type::Input;
}

inline void Input::SetTitle(System::String ^ _title)
{
    this->title = _title;
}

inline void Input::SetPlaceHolder(System::String ^ _placeholder)
{
    this->placeholder = _placeholder;
}

inline void Input::SetDefault(System::String ^ _def)
{
    this->def = _def;
}


inline Toggle::Toggle(System::String ^ name, System::String ^ title, bool def)
    : title(title)
    , def(def)
{
    SetName(name);
}

inline Toggle::Toggle(System::String ^ name, System::String ^ title)
    : title(title)
    , def(false)
{
    SetName(name);
}

inline Toggle::Type Toggle::GetType()
{
    return Type::Toggle;
}

inline void Toggle::SetTitle(System::String ^ _title)
{
    this->title = _title;
}

inline void Toggle::SetDefault(bool _def)
{
    this->def = _def;
}


inline Dropdown::Dropdown(System::String ^ name, System::String ^ title, List<System::String ^> ^ options, int defId)
    : title(title)
    , options(options)
    , def(defId)
{
    SetName(name);
}

inline Dropdown::Dropdown(System::String ^ name, System::String ^ title, List<System::String ^> ^ options)
    : title(title)
    , options(options)
    , def(0)
{
    SetName(name);
}

inline Dropdown::Type Dropdown::GetType()
{
    return Type::Dropdown;
}

inline void Dropdown::SetTitle(System::String ^ _title)
{
    this->title = _title;
}

inline void Dropdown::SetOptions(List<System::String ^> ^ _options)
{
    this->options = _options;
}

inline void Dropdown::AddOption(System::String ^ option)
{
    if (options != nullptr) options->Add(option);
}

inline void Dropdown::SetDefault(int defId)
{
    this->def = defId;
}


inline Slider::Slider(System::String ^ name, System::String ^ title, int min, int max, int step, int def)
    : title(title)
    , min(min)
    , max(max)
    , step(step)
    , def(def)
{
    SetName(name);
}

inline Slider::Slider(System::String ^ name, System::String ^ title, int min, int max, int step)
    : title(title)
    , min(min)
    , max(max)
    , step(step)
    , def(0)
{
    SetName(name);
}

inline Slider::Slider(System::String ^ name, System::String ^ title, int min, int max)
    : title(title)
    , min(min)
    , max(max)
    , step(1)
    , def(0)
{
    SetName(name);
}

inline Slider::Type Slider::GetType()
{
    return Type::Slider;
}

inline void Slider::SetTitle(System::String ^ _title)
{
    this->title = _title;
}

inline void Slider::SetMin(int _min)
{
    this->min = _min;
}

inline void Slider::SetMax(int _max)
{
    this->max = _max;
}

inline void Slider::SetStep(int _step)
{
    this->step = _step;
}

inline void Slider::SetDefault(int _def)
{
    this->def = _def;
}


inline StepSlider::StepSlider(System::String ^ name, System::String ^ title, List<System::String ^> ^ options, int defId)
    : title(title)
    , options(options)
    , def(defId)
{
    SetName(name);
}

inline StepSlider::StepSlider(System::String ^ name, System::String ^ title, List<System::String ^> ^ options)
    : title(title)
    , options(options)
    , def(0)
{
    SetName(name);
}

inline StepSlider::Type StepSlider::GetType()
{
    return Type::StepSlider;
}

inline void StepSlider::SetTitle(System::String ^ _title)
{
    this->title = _title;
}

inline void StepSlider::SetOptions(List<System::String ^> ^ _options)
{
    this->options = _options;
}

inline void StepSlider::AddOption(System::String ^ option)
{
    if (options != nullptr) options->Add(option);
}

inline void StepSlider::SetDefault(int defId)
{
    this->def = defId;
}


SimpleForm::SimpleForm(System::String ^ title, System::String ^ content)
    : title(title)
    , content(content)
{
    elements = gcnew List<SimpleFormElement ^>;
    gchList = gcnew List<GCHandle>;
}

inline SimpleForm ^ SimpleForm::Append(Button ^ element)
{
    elements->Add((SimpleFormElement ^) element);
    return this;
}

inline SimpleForm ^ SimpleForm::SetTitle(System::String ^ title)
{
    this->title = title;
    return this;
}

inline SimpleForm ^ SimpleForm::CstContent(System::String ^ content)
{
    this->content = content;
    return this;
}

inline SimpleForm ^ SimpleForm::AddButton(System::String ^ text, System::String ^ image, Button::ButtonCallback ^ callback)
{
    return Append(gcnew Button(text, image, callback));
}

inline SimpleForm ^ SimpleForm::AddButton(System::String ^ text, System::String ^ image)
{
    return Append(gcnew Button(text, image));
}

inline SimpleForm ^ SimpleForm::AddButton(System::String ^ text)
{
    return Append(gcnew Button(text));
}

bool SimpleForm::SendTo(MC::Player ^ _player, Callback ^ _callback)
{
    callback = _callback == nullptr ? callback : _callback;
    typedef void (*FnPtr)(::Player*, int);
    ::Form::SimpleForm::Callback pfunc = nullptr;
    if (callback == nullptr)
    {
        pfunc = ::Form::SimpleForm::Callback();
        goto null;
    }
    auto defunc = gcnew _Callback(this, &SimpleForm::sendToFunc);
    gchList->Add(GCHandle::Alloc(defunc));
    pfunc = static_cast<FnPtr>(
        Marshal::GetFunctionPointerForDelegate(defunc).ToPointer());
null:
    ::Form::SimpleForm simpleform(marshalString<Encoding::E_UTF8>(title), marshalString<Encoding::E_UTF8>(content));
    for each (auto var in elements)
    {
        auto _var = ((Button ^) var);
        ::Form::Button button(marshalString<Encoding::E_UTF8>(_var->text), marshalString<Encoding::E_UTF8>(_var->image), _var->ToNativeCallback());
        simpleform.append(button);
    }

    return simpleform.sendTo(_player->NativePtr, pfunc);
}

inline bool SimpleForm::SendTo(MC::Player ^ player)
{
    ::Form::SimpleForm simpleform(marshalString<Encoding::E_UTF8>(title), marshalString<Encoding::E_UTF8>(content));
    return SendTo(player, nullptr);
}

SimpleForm::~SimpleForm()
{
    for each (GCHandle % var in gchList)
    {
        if (var.IsAllocated)
        {
            var.Free();
        }
    }
    delete elements;
    delete callback;
    delete gchList;
}

inline void NATIVECALLBACK SimpleForm::sendToFunc(::Player* p, int a)
{
    try
    {
        callback(gcnew MC::Player(p), a);
    }
    CATCH
}

CustomForm::CustomForm(System::String ^ title)
    : title(title)
{
    elements = gcnew List<kvPair>;
}

inline CustomForm ^ CustomForm::append(CustomFormElement ^ element)
{
    isFormGenerated = false;
    isDictionaryGenerated = false;
    elements->Add(kvPair(element->name, element));
    return this;
}

CustomForm::~CustomForm()
{
    delete nativeform;
    for each (GCHandle % var in gchList)
    {
        if (var.IsAllocated)
        {
            var.Free();
        }
    }
    delete gchList;
    delete elements;
    delete callback;
    delete CallbackDictionary;
}

void NATIVECALLBACK CustomForm::sendFunc(::Player* p, std::map<string, std::shared_ptr<::Form::CustomFormElement>> arg)
{

    if (!isDictionaryGenerated || CallbackDictionary == nullptr)
    {
        CallbackDictionary = gcnew Dictionary<System::String ^, CustomFormElement ^>;
        isDictionaryGenerated = true;

        for (auto iter = arg.begin(); iter != arg.end(); ++iter)
        {
            switch (iter->second->getType())
            {
                case ::Form::CustomFormElement::Type::Label:
                {
                    auto label = gcnew Label(
                        marshalString<Encoding::E_UTF8>(((::Form::Label*)iter->second.get())->name),
                        marshalString<Encoding::E_UTF8>(((::Form::Label*)iter->second.get())->text));
                    CallbackDictionary->Add(marshalString<Encoding::E_UTF8>(iter->first), label);
                }
                break;
                case ::Form::CustomFormElement::Type::Input:
                {
                    auto input = gcnew Input(
                        marshalString<Encoding::E_UTF8>(((::Form::Input*)iter->second.get())->name),
                        marshalString<Encoding::E_UTF8>(((::Form::Input*)iter->second.get())->title),
                        marshalString<Encoding::E_UTF8>(((::Form::Input*)iter->second.get())->placeholder),
                        marshalString<Encoding::E_UTF8>(((::Form::Input*)iter->second.get())->def));
                    CallbackDictionary->Add(marshalString<Encoding::E_UTF8>(iter->first), input);
                }
                break;
                case ::Form::CustomFormElement::Type::Toggle:
                {
                    auto toggle = gcnew Toggle(
                        marshalString<Encoding::E_UTF8>(((::Form::Toggle*)iter->second.get())->name),
                        marshalString<Encoding::E_UTF8>(((::Form::Toggle*)iter->second.get())->title),
                        ((::Form::Toggle*)iter->second.get())->def);
                    CallbackDictionary->Add(marshalString<Encoding::E_UTF8>(iter->first), toggle);
                }
                break;
                case ::Form::CustomFormElement::Type::Dropdown:
                {
                    auto dropdownSysList = gcnew List<System::String ^>;
                    for each (auto& var in ((::Form::Dropdown*)iter->second.get())->options)
                        dropdownSysList->Add(marshalString<Encoding::E_UTF8>(var));
                    auto dropdown = gcnew Dropdown(
                        marshalString<Encoding::E_UTF8>(((::Form::Dropdown*)iter->second.get())->name),
                        marshalString<Encoding::E_UTF8>(((::Form::Dropdown*)iter->second.get())->title),
                        dropdownSysList,
                        ((::Form::Dropdown*)iter->second.get())->def);
                    CallbackDictionary->Add(marshalString<Encoding::E_UTF8>(iter->first), dropdown);
                }
                break;
                case ::Form::CustomFormElement::Type::Slider:
                {
                    auto slider = gcnew Slider(
                        marshalString<Encoding::E_UTF8>(((::Form::Slider*)iter->second.get())->name),
                        marshalString<Encoding::E_UTF8>(((::Form::Slider*)iter->second.get())->title),
                        ((::Form::Slider*)iter->second.get())->minValue,
                        ((::Form::Slider*)iter->second.get())->maxValue,
                        ((::Form::Slider*)iter->second.get())->step,
                        ((::Form::Slider*)iter->second.get())->def);
                    CallbackDictionary->Add(marshalString<Encoding::E_UTF8>(iter->first), slider);
                }
                break;
                case ::Form::CustomFormElement::Type::StepSlider:
                {
                    auto stepsliderSysList = gcnew List<System::String ^>;
                    for each (auto& var in ((::Form::StepSlider*)iter->second.get())->options)
                        stepsliderSysList->Add(marshalString<Encoding::E_UTF8>(var));
                    auto stepslider = gcnew StepSlider(
                        marshalString<Encoding::E_UTF8>(((::Form::StepSlider*)iter->second.get())->name),
                        marshalString<Encoding::E_UTF8>(((::Form::StepSlider*)iter->second.get())->title),
                        stepsliderSysList,
                        ((::Form::StepSlider*)iter->second.get())->def);
                    CallbackDictionary->Add(marshalString<Encoding::E_UTF8>(iter->first), stepslider);
                }
                break;
            }
        }
    }
    if (callback != nullptr)
    {
        try
        {
            callback(gcnew MC::Player(p), CallbackDictionary);
        }
        CATCH
    }
}

bool CustomForm::sendTo(MC::Player ^ player, Callback ^ _callback)
{
    callback = _callback;
    if (gchList == nullptr) gchList = gcnew List<GCHandle>;

    auto defunc = gcnew de_sendFunc(this, &CustomForm::sendFunc);
    gchList->Add(GCHandle::Alloc(defunc));

    ::Form::CustomForm::Callback _callback_ = (callback == nullptr ? ::Form::CustomForm::Callback() : static_cast<void (*)(::Player*, std::map<string, std::shared_ptr<::Form::CustomFormElement>>)>(Marshal::GetFunctionPointerForDelegate(defunc).ToPointer()));

    if (!isFormGenerated || nativeform == nullptr)
    {
        delete nativeform;
        nativeform = nullptr;
        nativeform = GenerateNativeForm();
        isFormGenerated = true;
    }
    return nativeform->sendTo(((::ServerPlayer*)(::Player*)player->NativePtr), _callback_);
}

::Form::CustomForm* CustomForm::GenerateNativeForm()
{

    auto ret = new ::Form::CustomForm(marshalString<Encoding::E_UTF8>(title));
    for each (auto var in elements)
    {
        auto p = var.Value;
        switch (p->GetType())
        {
            case Form::CustomFormElement::Type::Label:
                ret->append(::Form::Label(
                    marshalString<Encoding::E_UTF8>(((Label ^) p)->name),
                    marshalString<Encoding::E_UTF8>(((Label ^) p)->text)));
                break;
            case Form::CustomFormElement::Type::Input:
                ret->append(::Form::Input(
                    marshalString<Encoding::E_UTF8>(((Input ^) p)->name),
                    marshalString<Encoding::E_UTF8>(((Input ^) p)->title),
                    marshalString<Encoding::E_UTF8>(((Input ^) p)->placeholder),
                    marshalString<Encoding::E_UTF8>(((Input ^) p)->def)));
                break;
            case Form::CustomFormElement::Type::Toggle:
                ret->append(::Form::Toggle(
                    marshalString<Encoding::E_UTF8>(((Toggle ^) p)->name),
                    marshalString<Encoding::E_UTF8>(((Toggle ^) p)->title),
                    ((Toggle ^) p)->def));
                break;
            case Form::CustomFormElement::Type::Dropdown:
            {
                std::vector<std::string> stdvector(((Dropdown ^) p)->options->Count);
                for (int i = 0, len = ((Dropdown ^) p)->options->Count; i < len; ++i)
                    stdvector[i] = std::move(marshalString<Encoding::E_UTF8>(((Dropdown ^) p)->options[i]));
                ret->append(::Form::Dropdown(
                    marshalString<Encoding::E_UTF8>(((Dropdown ^) p)->name),
                    marshalString<Encoding::E_UTF8>(((Dropdown ^) p)->title),
                    stdvector,
                    ((Dropdown ^) p)->def));
            }
            break;
            case Form::CustomFormElement::Type::Slider:
                ret->append(::Form::Slider(
                    marshalString<Encoding::E_UTF8>(((Slider ^) p)->name),
                    marshalString<Encoding::E_UTF8>(((Slider ^) p)->title),
                    ((Slider ^) p)->min,
                    ((Slider ^) p)->max,
                    ((Slider ^) p)->step,
                    ((Slider ^) p)->def));
                break;
            case Form::CustomFormElement::Type::StepSlider:
            {
                std::vector<std::string> stdvector(((StepSlider ^) p)->options->Count);
                for (int i = 0, len = ((StepSlider ^) p)->options->Count; i < len; ++i)
                    stdvector[i] = std::move(marshalString<Encoding::E_UTF8>(((StepSlider ^) p)->options[i]));
                ret->append(::Form::StepSlider(
                    marshalString<Encoding::E_UTF8>(((StepSlider ^) p)->name),
                    marshalString<Encoding::E_UTF8>(((StepSlider ^) p)->title),
                    stdvector,
                    ((StepSlider ^) p)->def));
            }
            break;
            default:
                break;
        }
    }
    return ret;
}

inline bool CustomForm::sendTo(MC::Player ^ player)
{
    return sendTo(player, nullptr);
}

inline CustomFormElement::Type CustomForm::GetType(int index)
{
    return CustomFormElement::Type(elements[index].Value->GetType());
}

inline System::String ^ CustomForm::GetString(System::String const ^ name)
{
    for each (auto % var in elements)
    {
        if (var.Key == name)
        {
            return var.Value->GetString();
        }
    }
    return "";
}
inline int CustomForm::GetNumber(System::String const ^ name)
{
    for each (auto % var in elements)
    {
        if (var.Key == name)
        {
            return var.Value->GetNumber();
        }
    }
    return 0;
}
inline bool CustomForm::GetBool(System::String const ^ name)
{
    for each (auto % var in elements)
    {
        if (var.Key == name)
        {
            return var.Value->GetBool();
        }
    }
    return false;
}
inline System::String ^ CustomForm::GetString(int index)
{
    return elements[index].Value->GetString();
}
inline int CustomForm::GetNumber(int index)
{
    return elements[index].Value->GetNumber();
}
inline bool CustomForm::GetBool(int index)
{
    return elements[index].Value->GetBool();
}

inline void CustomForm::SetValue(int index, System::String ^ value)
{
    elements[index].Value->value = value;
}
} // namespace LLNET::Form
