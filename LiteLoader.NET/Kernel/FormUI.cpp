#include "../Header/FormUI.hpp"



namespace LLNET::Form
{
inline Button::Button(String ^ text, String ^ image, ButtonCallback ^ callback)
    : text(text)
    , image(image)
    , callback(callback)
{
}

inline Button::Button(String ^ text, String ^ image)
    : text(text)
    , image(image)
    , callback(nullptr)
{
}

inline Button::Button(String ^ text)
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

inline void Button::SetText(String ^ text)
{
    this->text = text;
}
inline void Button::SetImage(String ^ image)
{
    this->image = image;
}
inline void Button::SetCallback(ButtonCallback ^ callback)
{
    this->callback = callback;
}

void NATIVECALLBACK Button::CallbackFn(::Player* p)
{
    try
    {
        callback(gcnew MC::Player(p));
    }
    CATCH
}

Button::pButtonCallback Button::ToNativeCallback()
{
    if (callback == nullptr)
        return pButtonCallback();
    auto de_callback = gcnew delButtonCallback(this, &Button::CallbackFn);
    gch = GCHandle::Alloc(de_callback);
    auto pfunc = static_cast<pButtonCallback>(
        Marshal::GetFunctionPointerForDelegate(de_callback).ToPointer());
    return pfunc;
}

inline void CustomFormElement::SetName(String ^ _name)
{
    this->name = _name;
}

inline String ^ CustomFormElement::GetString()
{
    return this->value;
}

inline int CustomFormElement::GetNumber()
{
    return System::Convert::ToInt32(value);
}

bool CustomFormElement::GetBool()
{
    if (String::IsNullOrEmpty(value) || value == "0" || value == "false" || value == "False" || value == "FALSE")
        return false;
    return true;
}


inline Label::Label(String ^ name, String ^ text)
    : text(text)
{
    SetName(name);
}

inline Label::Type Label::GetType()
{
    return Type::Label;
}

inline void Label::SetText(String ^ _text)
{
    this->text = _text;
}


inline Input::Input(String ^ name, String ^ title, String ^ placeholder, String ^ def)
    : title(title)
    , placeholder(placeholder)
    , def(def)
{
    SetName(name);
}

inline Input::Input(String ^ name, String ^ title, String ^ placeholder)
    : title(title)
    , placeholder(placeholder)
    , def("")
{
    SetName(name);
}

inline Input::Input(String ^ name, String ^ title)
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

inline void Input::SetTitle(String ^ title)
{
    this->title = title;
}

inline void Input::SetPlaceHolder(String ^ placeholder)
{
    this->placeholder = placeholder;
}

inline void Input::SetDefault(String ^ def)
{
    this->def = def;
}


inline Toggle::Toggle(String ^ name, String ^ title, bool def)
    : title(title)
    , def(def)
{
    SetName(name);
}

inline Toggle::Toggle(String ^ name, String ^ title)
    : title(title)
    , def(false)
{
    SetName(name);
}

inline Toggle::Type Toggle::GetType()
{
    return Type::Toggle;
}

inline void Toggle::SetTitle(String ^ title)
{
    this->title = title;
}

inline void Toggle::SetDefault(bool def)
{
    this->def = def;
}


inline Dropdown::Dropdown(String ^ name, String ^ title, List<String ^> ^ options, int defId)
    : title(title)
    , options(options)
    , def(defId)
{
    SetName(name);
}

inline Dropdown::Dropdown(String ^ name, String ^ title, List<String ^> ^ options)
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

inline void Dropdown::SetTitle(String ^ title)
{
    this->title = title;
}

inline void Dropdown::SetOptions(List<String ^> ^ options)
{
    this->options = options;
}

inline void Dropdown::AddOption(String ^ option)
{
    if (options != nullptr) options->Add(option);
}

inline void Dropdown::SetDefault(int defId)
{
    this->def = defId;
}


inline Slider::Slider(String ^ name, String ^ title, int min, int max, int step, int def)
    : title(title)
    , min(min)
    , max(max)
    , step(step)
    , def(def)
{
    SetName(name);
}

inline Slider::Slider(String ^ name, String ^ title, int min, int max, int step)
    : title(title)
    , min(min)
    , max(max)
    , step(step)
    , def(0)
{
    SetName(name);
}

inline Slider::Slider(String ^ name, String ^ title, int min, int max)
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

inline void Slider::SetTitle(String ^ title)
{
    this->title = title;
}

inline void Slider::SetMin(int min)
{
    this->min = min;
}

inline void Slider::SetMax(int max)
{
    this->max = max;
}

inline void Slider::SetStep(int step)
{
    this->step = step;
}

inline void Slider::SetDefault(int def)
{
    this->def = def;
}


inline StepSlider::StepSlider(String ^ name, String ^ title, List<String ^> ^ options, int defId)
    : title(title)
    , options(options)
    , def(defId)
{
    SetName(name);
}

inline StepSlider::StepSlider(String ^ name, String ^ title, List<String ^> ^ options)
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

inline void StepSlider::SetTitle(String ^ title)
{
    this->title = title;
}

inline void StepSlider::SetOptions(List<String ^> ^ options)
{
    this->options = options;
}

inline void StepSlider::AddOption(String ^ option)
{
    if (options != nullptr) options->Add(option);
}

inline void StepSlider::SetDefault(int defId)
{
    this->def = defId;
}


SimpleForm::SimpleForm(String ^ title, String ^ content)
    : title(title)
    , content(content)
{
    elements = gcnew List<SimpleFormElement ^>;
    callbackHandlerList = gcnew List<NativeCallbackHandler ^>;
}

inline SimpleForm ^ SimpleForm::Append(Button ^ element)
{
    elements->Add((SimpleFormElement ^) element);
    return this;
}

inline SimpleForm ^ SimpleForm::SetTitle(String ^ title)
{
    this->title = title;
    return this;
}

inline SimpleForm ^ SimpleForm::CstContent(String ^ content)
{
    this->content = content;
    return this;
}

inline SimpleForm ^ SimpleForm::AddButton(String ^ text, String ^ image, Button::ButtonCallback ^ callback)
{
    return Append(gcnew Button(text, image, callback));
}

inline SimpleForm ^ SimpleForm::AddButton(String ^ text, String ^ image)
{
    return Append(gcnew Button(text, image));
}

inline SimpleForm ^ SimpleForm::AddButton(String ^ text)
{
    return Append(gcnew Button(text));
}


NativeCallbackConvertHelper(SimpleFormCallbackHelper, SimpleForm::Callback, void, ::Player* pl, int a0)
{
    auto player = gcnew MC::Player(pl);
    try
    {
        delfunc(player, a0);
    }
    CATCH
    delete player;
}


bool SimpleForm::SendTo(MC::Player ^ player, Callback ^ callback)
{
    this->callback = callback == nullptr ? this->callback : callback;

    ::Form::SimpleForm::Callback pfunc = nullptr;
    if (this->callback == nullptr)
    {
        pfunc = ::Form::SimpleForm::Callback();
        goto null;
    }

    {
        auto pair = SimpleFormCallbackHelper::Create(this->callback);
        pfunc = pair.pCallbackFn;
        callbackHandlerList->Add(pair.converter);
    }

null:
    ::Form::SimpleForm simpleform(marshalString(title), marshalString(content));
    for each (auto var in elements)
    {
        auto _var = ((Button ^) var);
        ::Form::Button button(marshalString(_var->Text), marshalString(_var->Image), _var->ToNativeCallback());
        simpleform.append(button);
    }

    return simpleform.sendTo(player->NativePtr, pfunc);
}

inline bool SimpleForm::SendTo(MC::Player ^ player)
{
    ::Form::SimpleForm simpleform(marshalString(title), marshalString(content));
    return SendTo(player, nullptr);
}

SimpleForm::!SimpleForm()
{
    for each (NativeCallbackHandler ^ var in callbackHandlerList)
    {
        delete var;
    }
    delete elements;
}

SimpleForm::~SimpleForm()
{
    this->!SimpleForm();
}

inline void NATIVECALLBACK SimpleForm::sendToFunc(::Player* p, int a)
{
    try
    {
        callback(gcnew MC::Player(p), a);
    }
    CATCH
}

CustomForm::CustomForm(String ^ title)
    : title(title)
{
    elements = gcnew List<kvPair>;
}

inline CustomForm ^ CustomForm::Append(CustomFormElement ^ element)
{
    isFormGenerated = false;
    isDictionaryGenerated = false;
    elements->Add(kvPair(element->Name, element));
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
        CallbackDictionary = gcnew Dictionary<String ^, CustomFormElement ^>;
        isDictionaryGenerated = true;

        for (auto iter = arg.begin(); iter != arg.end(); ++iter)
        {
            switch (iter->second->getType())
            {
                case ::Form::CustomFormElement::Type::Label:
                {
                    auto label = gcnew Label(
                        marshalString(((::Form::Label*)iter->second.get())->name),
                        marshalString(((::Form::Label*)iter->second.get())->text));
                    CallbackDictionary->Add(marshalString(iter->first), label);
                }
                break;
                case ::Form::CustomFormElement::Type::Input:
                {
                    auto input = gcnew Input(
                        marshalString(((::Form::Input*)iter->second.get())->name),
                        marshalString(((::Form::Input*)iter->second.get())->title),
                        marshalString(((::Form::Input*)iter->second.get())->placeholder),
                        marshalString(((::Form::Input*)iter->second.get())->def));
                    CallbackDictionary->Add(marshalString(iter->first), input);
                }
                break;
                case ::Form::CustomFormElement::Type::Toggle:
                {
                    auto toggle = gcnew Toggle(
                        marshalString(((::Form::Toggle*)iter->second.get())->name),
                        marshalString(((::Form::Toggle*)iter->second.get())->title),
                        ((::Form::Toggle*)iter->second.get())->def);
                    CallbackDictionary->Add(marshalString(iter->first), toggle);
                }
                break;
                case ::Form::CustomFormElement::Type::Dropdown:
                {
                    auto dropdownSysList = gcnew List<String ^>;
                    for each (auto& var in ((::Form::Dropdown*)iter->second.get())->options)
                        dropdownSysList->Add(marshalString(var));
                    auto dropdown = gcnew Dropdown(
                        marshalString(((::Form::Dropdown*)iter->second.get())->name),
                        marshalString(((::Form::Dropdown*)iter->second.get())->title),
                        dropdownSysList,
                        ((::Form::Dropdown*)iter->second.get())->def);
                    CallbackDictionary->Add(marshalString(iter->first), dropdown);
                }
                break;
                case ::Form::CustomFormElement::Type::Slider:
                {
                    auto slider = gcnew Slider(
                        marshalString(((::Form::Slider*)iter->second.get())->name),
                        marshalString(((::Form::Slider*)iter->second.get())->title),
                        ((::Form::Slider*)iter->second.get())->minValue,
                        ((::Form::Slider*)iter->second.get())->maxValue,
                        ((::Form::Slider*)iter->second.get())->step,
                        ((::Form::Slider*)iter->second.get())->def);
                    CallbackDictionary->Add(marshalString(iter->first), slider);
                }
                break;
                case ::Form::CustomFormElement::Type::StepSlider:
                {
                    auto stepsliderSysList = gcnew List<String ^>;
                    for each (auto& var in ((::Form::StepSlider*)iter->second.get())->options)
                        stepsliderSysList->Add(marshalString(var));
                    auto stepslider = gcnew StepSlider(
                        marshalString(((::Form::StepSlider*)iter->second.get())->name),
                        marshalString(((::Form::StepSlider*)iter->second.get())->title),
                        stepsliderSysList,
                        ((::Form::StepSlider*)iter->second.get())->def);
                    CallbackDictionary->Add(marshalString(iter->first), stepslider);
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

bool CustomForm::SendTo(MC::Player ^ player, Callback ^ _callback)
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

    auto ret = new ::Form::CustomForm(marshalString(title));
    for each (auto var in elements)
    {
        auto p = var.Value;
        switch (p->GetType())
        {
            case Form::CustomFormElement::Type::Label:
                ret->append(::Form::Label(
                    marshalString(((Label ^) p)->Name),
                    marshalString(((Label ^) p)->Text)));
                break;
            case Form::CustomFormElement::Type::Input:
                ret->append(::Form::Input(
                    marshalString(((Input ^) p)->Name),
                    marshalString(((Input ^) p)->Title),
                    marshalString(((Input ^) p)->Placeholder),
                    marshalString(((Input ^) p)->Def)));
                break;
            case Form::CustomFormElement::Type::Toggle:
                ret->append(::Form::Toggle(
                    marshalString(((Toggle ^) p)->Name),
                    marshalString(((Toggle ^) p)->Title),
                    ((Toggle ^) p)->Def));
                break;
            case Form::CustomFormElement::Type::Dropdown:
            {
                std::vector<std::string> stdvector(((Dropdown ^) p)->Options->Count);
                for (int i = 0, len = ((Dropdown ^) p)->Options->Count; i < len; ++i)
                    stdvector[i] = std::move(marshalString(((Dropdown ^) p)->Options[i]));
                ret->append(::Form::Dropdown(
                    marshalString(((Dropdown ^) p)->Name),
                    marshalString(((Dropdown ^) p)->Title),
                    stdvector,
                    ((Dropdown ^) p)->Def));
            }
            break;
            case Form::CustomFormElement::Type::Slider:
                ret->append(::Form::Slider(
                    marshalString(((Slider ^) p)->Name),
                    marshalString(((Slider ^) p)->Title),
                    ((Slider ^) p)->Min,
                    ((Slider ^) p)->Max,
                    ((Slider ^) p)->Step,
                    ((Slider ^) p)->Def));
                break;
            case Form::CustomFormElement::Type::StepSlider:
            {
                std::vector<std::string> stdvector(((StepSlider ^) p)->Options->Count);
                for (int i = 0, len = ((StepSlider ^) p)->Options->Count; i < len; ++i)
                    stdvector[i] = std::move(marshalString(((StepSlider ^) p)->Options[i]));
                ret->append(::Form::StepSlider(
                    marshalString(((StepSlider ^) p)->Name),
                    marshalString(((StepSlider ^) p)->Title),
                    stdvector,
                    ((StepSlider ^) p)->Def));
            }
            break;
            default:
                break;
        }
    }
    return ret;
}

inline bool CustomForm::SendTo(MC::Player ^ player)
{
    return SendTo(player, nullptr);
}

inline CustomFormElement::Type CustomForm::GetType(int index)
{
    return CustomFormElement::Type(elements[index].Value->GetType());
}

inline String ^ CustomForm::GetString(String const ^ name)
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
inline int CustomForm::GetNumber(String const ^ name)
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
inline bool CustomForm::GetBool(String const ^ name)
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
inline String ^ CustomForm::GetString(int index)
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

inline void CustomForm::SetValue(int index, String ^ value)
{
    elements[index].Value->Value = value;
}
} // namespace LLNET::Form
