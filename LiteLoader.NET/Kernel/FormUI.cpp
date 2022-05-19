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

inline Button::!Button()
{
    for each (auto var in handlers)
    {
        delete var;
    }
}

inline Button::~Button()
{
    this->!Button();
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

DelegateToNativeHelper(ButtonCallbackHelper, Button::ButtonCallback, void, ::Player* pl)
{
    auto player = gcnew MC::Player(pl);

    try
    {
        delfunc(player);
    }
    CATCH

    delete player;
}

Button::pButtonCallback Button::ToNativeCallback()
{
    if (callback == nullptr)
        return pButtonCallback();

    auto pair = ButtonCallbackHelper::Create(callback);
    handlers->Add(pair.converter);
    return pair.pCallbackFn;
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


DelegateToNativeHelper(SimpleFormCallbackHelper, SimpleForm::SimpleFormCallback, void, ::Player* pl, int a0)
{
    auto player = gcnew MC::Player(pl);
    try
    {
        delfunc(player, a0);
    }
    CATCH
    delete player;
}


bool SimpleForm::SendTo(MC::Player ^ player, SimpleFormCallback ^ callback)
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
        handlers->Add(pair.converter);
    }

null:
    ::Form::SimpleForm simpleform(marshalString(title), marshalString(content));
    for each (Button ^ var in elements)
    {
        ::Form::Button button(marshalString(var->Text), marshalString(var->Image), var->ToNativeCallback());

        simpleform.append(button);
    }

    return simpleform.sendTo(player->NativePtr, pfunc);
}

inline bool SimpleForm::SendTo(MC::Player ^ player)
{
    return SendTo(player, nullptr);
}

SimpleForm::!SimpleForm()
{
    for each (auto var in handlers)
    {
        delete var;
    }
    delete elements;
}

SimpleForm::~SimpleForm()
{
    this->!SimpleForm();
}

CustomForm::CustomForm(String ^ title)
    : title(title)
{
}

inline CustomForm ^ CustomForm::Append(CustomFormElement ^ element)
{
    isFormGenerated = false;
    isDictionaryGenerated = false;
    elements->Add(kvPair(element->Name, element));
    return this;
}

LLNET::Form::CustomForm::!CustomForm()
{
    for each (auto var in handlers)
    {
        delete var;
    }
    delete CallbackDictionary;
    delete elements;
}

CustomForm::~CustomForm()
{
    this->!CustomForm();
}

void NATIVECALLBACK CustomForm::NativeFormSendCallback(::Player* p, std::map<string, std::shared_ptr<::Form::CustomFormElement>> arg)
{

    if (CallbackDictionary == nullptr || !isDictionaryGenerated)
    {
        CallbackDictionary = gcnew Dictionary<String ^, CustomFormElement ^>;
        isDictionaryGenerated = true;

        for (auto& mapPair : arg)
        {
            switch (mapPair.second->getType())
            {
                case ::Form::CustomFormElement::Type::Label:
                {
                    auto label = _Marshal(*static_cast<::Form::Label*>(mapPair.second.get()));
                    CallbackDictionary->Add(marshalString(mapPair.first), label);
                }
                break;
                case ::Form::CustomFormElement::Type::Input:
                {
                    auto input = _Marshal(*static_cast<::Form::Input*>(mapPair.second.get()));
                    CallbackDictionary->Add(marshalString(mapPair.first), input);
                }
                break;
                case ::Form::CustomFormElement::Type::Toggle:
                {
                    auto toggle = _Marshal(*static_cast<::Form::Toggle*>(mapPair.second.get()));
                    CallbackDictionary->Add(marshalString(mapPair.first), toggle);
                }
                break;
                case ::Form::CustomFormElement::Type::Dropdown:
                {
                    auto dropdown = _Marshal(*static_cast<::Form::Dropdown*>(mapPair.second.get()));
                    CallbackDictionary->Add(marshalString(mapPair.first), dropdown);
                }
                break;
                case ::Form::CustomFormElement::Type::Slider:
                {
                    auto slider = _Marshal(*static_cast<::Form::Slider*>(mapPair.second.get()));
                    CallbackDictionary->Add(marshalString(mapPair.first), slider);
                }
                break;
                case ::Form::CustomFormElement::Type::StepSlider:
                {
                    auto stepSlider = _Marshal(*static_cast<::Form::StepSlider*>(mapPair.second.get()));
                    CallbackDictionary->Add(marshalString(mapPair.first), stepSlider);
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

bool CustomForm::SendTo(MC::Player ^ player, CustomFormCallback ^ callback)
{
    this->callback = callback;

    auto defunc = gcnew delSendCallback(this, &CustomForm::NativeFormSendCallback);

    ::Form::CustomForm::Callback _callback = (this->callback == nullptr ? ::Form::CustomForm::Callback() : static_cast<void (*)(::Player*, std::map<string, std::shared_ptr<::Form::CustomFormElement>>)>(Marshal::GetFunctionPointerForDelegate(defunc).ToPointer()));

    if (NativePtr == nullptr || !isFormGenerated)
    {
        delete NativePtr;
        GenerateNativeForm();
        isFormGenerated = true;
    }
    return NativePtr->sendTo(((::ServerPlayer*)static_cast<::Player*>(player->NativePtr)), _callback);
}


void CustomForm::GenerateNativeForm()
{

    NativePtr = new ::Form::CustomForm(marshalString(title));
    for each (auto var in elements)
    {
        auto p = var.Value;
        switch (p->GetType())
        {
            case Form::CustomFormElement::Type::Label:
                NativePtr->append(_Marshal(static_cast<Label ^>(p)));
                break;
            case Form::CustomFormElement::Type::Input:
                NativePtr->append(_Marshal(static_cast<Input ^>(p)));
                break;
            case Form::CustomFormElement::Type::Toggle:
                NativePtr->append(_Marshal(static_cast<Toggle ^>(p)));

                break;
            case Form::CustomFormElement::Type::Dropdown:
            {
                std::vector<std::string> stdvector;
                stdvector.resize(static_cast<Dropdown ^>(p)->Options->Count);
                for each (auto var in static_cast<Dropdown ^>(p)->Options)
                {
                    stdvector.emplace_back(marshalString(var));
                }
                NativePtr->append(_Marshal(static_cast<Dropdown ^>(p)));
            }
            break;
            case Form::CustomFormElement::Type::Slider:
                NativePtr->append(_Marshal(static_cast<Slider ^>(p)));

                break;
            case Form::CustomFormElement::Type::StepSlider:
            {
                std::vector<std::string> stdvector;
                stdvector.resize(static_cast<StepSlider ^>(p)->Options->Count);
                for each (auto var in static_cast<StepSlider ^>(p)->Options)
                {
                    stdvector.emplace_back(marshalString(var));
                }
                NativePtr->append(_Marshal(static_cast<StepSlider ^>(p)));
            }
            break;
            default:
                break;
        }
    }
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


inline ::Form::Label CustomForm::_Marshal(Label ^ arg)
{
    return ::Form::Label(
        marshalString(arg->Name),
        marshalString(arg->Text));
}

inline ::Form::Input CustomForm::_Marshal(Input ^ arg)
{
    return ::Form::Input(
        marshalString(arg->Name),
        marshalString(arg->Title),
        marshalString(arg->Placeholder),
        marshalString(arg->Def));
}

inline ::Form::Toggle CustomForm::_Marshal(Toggle ^ arg)
{
    return ::Form::Toggle(
        marshalString(arg->Name),
        marshalString(arg->Title),
        arg->Def);
}

inline ::Form::Slider CustomForm::_Marshal(Slider ^ arg)
{
    return ::Form::Slider(
        marshalString(arg->Name),
        marshalString(arg->Title),
        arg->Min,
        arg->Max,
        arg->Step,
        arg->Def);
}

inline ::Form::Dropdown CustomForm::_Marshal(Dropdown ^ arg)
{
    std::vector<std::string> stdvector;

    stdvector.resize(arg->Options->Count);

    for each (auto option in arg->Options)
    {
        stdvector.emplace_back(marshalString(option));
    }

    return ::Form::Dropdown(
        marshalString(arg->Name),
        marshalString(arg->Title),
        stdvector,
        arg->Def);
}

inline ::Form::StepSlider CustomForm::_Marshal(StepSlider ^ arg)
{
    std::vector<std::string> stdvector;

    stdvector.resize(arg->Options->Count);

    for each (auto option in arg->Options)
    {
        stdvector.emplace_back(marshalString(option));
    }

    return ::Form::StepSlider(
        marshalString(arg->Name),
        marshalString(arg->Title),
        stdvector,
        arg->Def);
}

inline Label ^ CustomForm::_Marshal(::Form::Label const& arg)
{
    return gcnew Label(
        marshalString(arg.name),
        marshalString(arg.text));
}

inline Input ^ CustomForm::_Marshal(::Form::Input const& arg)
{
    return gcnew Input(
        marshalString(arg.name),
        marshalString(arg.title),
        marshalString(arg.placeholder),
        marshalString(arg.def));
}

inline Toggle ^ CustomForm::_Marshal(::Form::Toggle const& arg)
{
    return gcnew Toggle(
        marshalString(arg.name),
        marshalString(arg.title),
        arg.def);
}

inline Slider ^ CustomForm::_Marshal(::Form::Slider const& arg)
{
    return gcnew Slider(
        marshalString(arg.name),
        marshalString(arg.title),
        arg.minValue,
        arg.maxValue,
        arg.step,
        arg.def);
}

inline Dropdown ^ CustomForm::_Marshal(::Form::Dropdown const& arg)
{
    auto dropdownSysList = gcnew List<String ^>(int(arg.options.size()));

    for each (auto& var in arg.options)
        dropdownSysList->Add(marshalString(var));

    return gcnew Dropdown(
        marshalString(arg.name),
        marshalString(arg.title),
        dropdownSysList,
        arg.def);
}

inline StepSlider ^ CustomForm::_Marshal(::Form::StepSlider const& arg)
{
    auto stepsliderSysList = gcnew List<String ^>(int(arg.options.size()));

    for each (auto& var in arg.options)
        stepsliderSysList->Add(marshalString(var));

    return gcnew StepSlider(
        marshalString(arg.name),
        marshalString(arg.title),
        stepsliderSysList,
        arg.def);
}

} // namespace LLNET::Form
