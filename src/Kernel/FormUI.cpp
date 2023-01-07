#include <src/Header/FormUI.hpp>

#include <src/Header/MC/Player.hpp>

#include <src/Header/Logger/Logger.hpp>


namespace LiteLoader::Form
{
    //////////////////////////////// Simple Form ////////////////////////////////

    inline Button::Button(String^ text, String^ image, ButtonCallback^ callback)
    {
        Text = text;
        Image = image;
        Callback = callback;
    }

    inline Button::Button(String^ text, String^ image)
        : Button(text, image, nullptr)
    {
    }

    inline Button::Button(String^ text)
        : Button(text, String::Empty, nullptr)
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

    DelegateToNativeHelper(ButtonCallbackHelper, Button::ButtonCallback, void, ::Player* pl)
    {
        auto player = gcnew MC::Player(pl);

        try
        {
            delfunc(player);
        }
        CATCH
    }

    Button::pButtonCallback Button::ToNativeCallback()
    {
        if (Callback == nullptr)
            return pButtonCallback();

        auto pair = ButtonCallbackHelper::Create(Callback);
        handlers->Add(pair.converter);
        return pair.pCallbackFn;
    }

    SimpleForm::SimpleForm(String^ title, String^ content)
    {
        Title = title;
        Content = content;
        Elements = gcnew List<SimpleFormElement^>;
    }

    inline SimpleForm^ SimpleForm::Append(Button^ element)
    {
        Elements->Add(element);
        return this;
    }

    inline SimpleForm^ SimpleForm::AddButton(String^ text, String^ image, Button::ButtonCallback^ callback)
    {
        return Append(gcnew Button(text, image, callback));
    }

    inline SimpleForm^ SimpleForm::AddButton(String^ text, String^ image)
    {
        return Append(gcnew Button(text, image));
    }

    inline SimpleForm^ SimpleForm::AddButton(String^ text)
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
    }

    bool SimpleForm::SendTo(MC::Player^ player, SimpleFormCallback^ callback)
    {
        if (callback != nullptr)
        {
            Callback = callback;
        }

        ::Form::SimpleForm::Callback pfunc;
        if (Callback != nullptr)
        {
            auto pair = SimpleFormCallbackHelper::Create(Callback);
            pfunc = pair.pCallbackFn;
            handlers->Add(pair.converter);
        }
        else
        {
            pfunc = ::Form::SimpleForm::Callback();
        }

        ::Form::SimpleForm simpleForm(marshalString(Title), marshalString(Content));
        for each (Button^ var in Elements)
        {
            ::Form::Button button(marshalString(var->Text), marshalString(var->Image), var->ToNativeCallback());
            simpleForm.append(button);
        }

        return simpleForm.sendTo(player->NativePtr, pfunc);
    }

    inline bool SimpleForm::SendTo(MC::Player^ player)
    {
        return SendTo(player, nullptr);
    }

    SimpleForm::!SimpleForm()
    {
        for each (auto var in handlers)
        {
            delete var;
        }
        delete Elements;
    }

    SimpleForm::~SimpleForm()
    {
        this->!SimpleForm();
    }

    //////////////////////////////// Modal Form ////////////////////////////////

    ModalForm::ModalForm(String^ title, String^ content, String^ confirmButton, String^ cancelButton)
    {
        Title = title;
        Content = content;
        ConfirmButton = confirmButton;
        CancelButton = cancelButton;
    }

    DelegateToNativeHelper(ModalFormCallbackHelper, ModalForm::ModalFormCallback, void, ::Player* pl, bool isConfirm)
    {
        auto player = gcnew MC::Player(pl);
        try
        {
            delfunc(player, isConfirm);
        }
        CATCH
    }

    bool ModalForm::SendTo(MC::Player^ player, ModalFormCallback^ callback)
    {
        if (callback != nullptr)
        {
            Callback = callback;
        }

        ::Form::ModalForm::Callback pfunc;
        if (Callback != nullptr)
        {
            auto pair = ModalFormCallbackHelper::Create(Callback);
            pfunc = pair.pCallbackFn;
            handlers->Add(pair.converter);
        }
        else
        {
            pfunc = ::Form::ModalForm::Callback();
        }

        ::Form::ModalForm modalForm(marshalString(Title), marshalString(Content), marshalString(ConfirmButton),
                                    marshalString(CancelButton));

        return modalForm.sendTo(player->NativePtr, pfunc);
    }

    inline bool ModalForm::SendTo(MC::Player^ player)
    {
        return SendTo(player, nullptr);
    }

    ModalForm::!ModalForm()
    {
        for each (auto var in handlers)
        {
            delete var;
        }
    }

    ModalForm::~ModalForm()
    {
        this->!ModalForm();
    }

    //////////////////////////////// Custom Form ////////////////////////////////

    inline String^ CustomFormElement::GetString()
    {
        return Value;
    }

    inline int CustomFormElement::GetInt()
    {
        return System::Convert::ToInt32(Value);
    }

    inline float CustomFormElement::GetFloat()
    {
        return System::Convert::ToSingle(Value);
    }

    inline double CustomFormElement::GetDouble()
    {
        return System::Convert::ToDouble(Value);
    }

    inline bool CustomFormElement::GetBool()
    {
        if (String::IsNullOrWhiteSpace(Value) || Value == "0" || Value->ToUpperInvariant() == "FALSE")
            return false;
        return true;
    }

    void CustomFormElement::reSetGeneratedForm()
    {
        for each (auto var in appendedForms)
        {
            var->IsFormGenerated = false;
        }
    }


    inline Label::Label(String^ name, String^ text)
    {
        Name = name;
        this->text = text;
    }


    inline Input::Input(String^ name, String^ title, String^ placeholder, String^ def)
    {
        Name = name;
        this->title = title,
            this->placeholder = placeholder;
        this->def = def;
    }

    inline Input::Input(String^ name, String^ title, String^ placeholder)
        : Input(name, title, placeholder, String::Empty)
    {
    }

    inline Input::Input(String^ name, String^ title)
        : Input(name, title, String::Empty, String::Empty)
    {
    }


    inline Toggle::Toggle(String^ name, String^ title, bool def)
    {
        Name = name;
        this->title = title;
        this->def = def;
    }

    inline Toggle::Toggle(String^ name, String^ title)
        : Toggle(name, title, false)
    {
    }


    inline Dropdown::Dropdown(String^ name, String^ title, List<String^>^ options, int defId)
    {
        Name = name;
        this->title = title;
        this->options = options;
        this->def = defId;
    }

    inline Dropdown::Dropdown(String^ name, String^ title, List<String^>^ options)
        : Dropdown(name, title, options, 0)
    {
    }

    inline void Dropdown::AddOption(String^ option)
    {
        if (options != nullptr)
        {
            options->Add(option);
        }
        reSetGeneratedForm();
    }


    inline Slider::Slider(String^ name, String^ title, double min, double max, double step, double def)
    {
        Name = name;
        this->title = title;
        this->min = min;
        this->max = max;
        this->step = step;
        this->def = def;
    }

    inline Slider::Slider(String^ name, String^ title, double min, double max, double step)
        : Slider(name, title, min, max, step, 0)
    {
    }

    inline Slider::Slider(String^ name, String^ title, double min, double max)
        : Slider(name, title, min, max, 1, 0)
    {
    }


    inline StepSlider::StepSlider(String^ name, String^ title, List<String^>^ options, int defId)
    {
        Name = name;
        this->title = title;
        this->options = options;
        this->def = defId;
    }

    inline StepSlider::StepSlider(String^ name, String^ title, List<String^>^ options)
        : StepSlider(name, title, options, 0)
    {
    }

    inline void StepSlider::AddOption(String^ option)
    {
        if (options != nullptr) options->Add(option);
        reSetGeneratedForm();
    }


    CustomForm::CustomForm(String^ title)
    {
        Title = title;
    }

    CustomForm::!CustomForm()
    {
        for each (auto var in handlers)
        {
            delete var;
        }
        delete elements;
    }

    CustomForm::~CustomForm()
    {
        this->!CustomForm();
    }

    void NATIVECALLBACK CustomForm::NativeFormSendCallback(
        Player* p, std::map<string, std::shared_ptr<::Form::CustomFormElement>> arg)
    {
        auto CallbackDictionary = gcnew Dictionary<String^, CustomFormElement^>(static_cast<int>(arg.size()));

        int index = 0;
        for (auto& [k, v] : arg)
        {
            switch (v->getType())
            {
            case ::Form::CustomFormElement::Type::Label:
                {
                    auto label = _Marshal(*static_cast<::Form::Label*>(v.get()));
                    label->Value = marshalString(v->getString());
                    CallbackDictionary->Add(marshalString(k), label);
                }
                break;
            case ::Form::CustomFormElement::Type::Input:
                {
                    auto input = _Marshal(*static_cast<::Form::Input*>(v.get()));
                    input->Value = marshalString(v->getString());
                    CallbackDictionary->Add(marshalString(k), input);
                }
                break;
            case ::Form::CustomFormElement::Type::Toggle:
                {
                    auto toggle = _Marshal(*static_cast<::Form::Toggle*>(v.get()));
                    toggle->Value = marshalString(v->getString());
                    CallbackDictionary->Add(marshalString(k), toggle);
                }
                break;
            case ::Form::CustomFormElement::Type::Dropdown:
                {
                    auto dropdown = _Marshal(*static_cast<::Form::Dropdown*>(v.get()));
                    dropdown->Value = marshalString(v->getString());
                    CallbackDictionary->Add(marshalString(k), dropdown);
                }
                break;
            case ::Form::CustomFormElement::Type::Slider:
                {
                    auto slider = _Marshal(*static_cast<::Form::Slider*>(v.get()));
                    slider->Value = marshalString(v->getString());
                    CallbackDictionary->Add(marshalString(k), slider);
                }
                break;
            case ::Form::CustomFormElement::Type::StepSlider:
                {
                    auto stepSlider = _Marshal(*static_cast<::Form::StepSlider*>(v.get()));
                    stepSlider->Value = marshalString(v->getString());
                    CallbackDictionary->Add(marshalString(k), stepSlider);
                }
                break;
            }

            ++index;
        }
        if (Callback != nullptr)
        {
            try
            {
                Callback(gcnew MC::Player(p), CallbackDictionary);
            }
            CATCH
        }
    }

    void CustomForm::GenerateNativeForm()
    {
        NativePtr = new ::Form::CustomForm(marshalString(Title));
        for each (auto var in elements)
        {
            auto p = var.Item2;
            switch (p->ElementType)
            {
            case CustomFormElement::Type::Label:
                NativePtr->append(_Marshal(static_cast<Label^>(p)));
                break;
            case CustomFormElement::Type::Input:
                NativePtr->append(_Marshal(static_cast<Input^>(p)));
                break;
            case CustomFormElement::Type::Toggle:
                NativePtr->append(_Marshal(static_cast<Toggle^>(p)));
                break;
            case CustomFormElement::Type::Dropdown:
                {
                    std::vector<std::string> stdvector;
                    for each (auto var in static_cast<Dropdown^>(p)->Options)
                    {
                        stdvector.emplace_back(marshalString(var));
                    }
                    NativePtr->append(_Marshal(static_cast<Dropdown^>(p)));
                }
                break;
            case CustomFormElement::Type::Slider:
                NativePtr->append(_Marshal(static_cast<Slider^>(p)));

                break;
            case CustomFormElement::Type::StepSlider:
                {
                    std::vector<std::string> stdvector;
                    for each (auto var in static_cast<StepSlider^>(p)->Options)
                    {
                        stdvector.emplace_back(marshalString(var));
                    }
                    NativePtr->append(_Marshal(static_cast<StepSlider^>(p)));
                }
                break;
            default:
                break;
            }
        }
    }

    inline CustomForm^ CustomForm::Append(CustomFormElement^ element)
    {
        isFormGenerated = false;
        elements->Add(kvPair(element->Name, element));
        if (!element->appendedForms->Contains(this))
            element->appendedForms->Add(this);
        return this;
    }

    bool CustomForm::SendTo(MC::Player^ player, CustomFormCallback^ callback)
    {
        if (callback != nullptr)
        {
            Callback = callback;
        }

        auto defunc = gcnew delSendCallback(this, &CustomForm::NativeFormSendCallback);

        const ::Form::CustomForm::Callback _callback
            = Callback == nullptr
                  ? ::Form::CustomForm::Callback()
                  : static_cast<void (*)(Player*, std::map<string, std::shared_ptr<::Form::CustomFormElement>>)>(
                      static_cast<void*>(Marshal::GetFunctionPointerForDelegate(defunc)));

        if (NativePtr == nullptr || !isFormGenerated)
        {
            delete NativePtr;
            GenerateNativeForm();
            isFormGenerated = true;
        }
        return NativePtr->sendTo(player->NativePtr, _callback);
    }

    inline bool CustomForm::SendTo(MC::Player^ player)
    {
        return SendTo(player, nullptr);
    }

    inline CustomFormElement^ CustomForm::GetElement(const String^ name)
    {
        for each (auto% var in elements)
        {
            if (var.Item1 == name)
            {
                return var.Item2;
            }
        }
        return nullptr;
    }

    inline CustomFormElement^ CustomForm::GetElement(int index)
    {
        return elements->Count > index ? elements[index].Item2 : nullptr;
    }


    inline ::Form::Label CustomForm::_Marshal(Label^ arg)
    {
        return ::Form::Label(
            marshalString(arg->Name),
            marshalString(arg->Text));
    }

    inline ::Form::Input CustomForm::_Marshal(Input^ arg)
    {
        return ::Form::Input(
            marshalString(arg->Name),
            marshalString(arg->Title),
            marshalString(arg->Placeholder),
            marshalString(arg->Def));
    }

    inline ::Form::Toggle CustomForm::_Marshal(Toggle^ arg)
    {
        return ::Form::Toggle(
            marshalString(arg->Name),
            marshalString(arg->Title),
            arg->Def);
    }

    inline ::Form::Slider CustomForm::_Marshal(Slider^ arg)
    {
        return ::Form::Slider(
            marshalString(arg->Name),
            marshalString(arg->Title),
            arg->Min,
            arg->Max,
            arg->Step,
            arg->Def);
    }

    inline ::Form::Dropdown CustomForm::_Marshal(Dropdown^ arg)
    {
        std::vector<std::string> stdvector;


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

    inline ::Form::StepSlider CustomForm::_Marshal(StepSlider^ arg)
    {
        std::vector<std::string> stdvector;


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

    inline Label^ CustomForm::_Marshal(const ::Form::Label& arg)
    {
        return gcnew Label(
            marshalString(arg.name),
            marshalString(arg.text));
    }

    inline Input^ CustomForm::_Marshal(const ::Form::Input& arg)
    {
        return gcnew Input(
            marshalString(arg.name),
            marshalString(arg.title),
            marshalString(arg.placeholder),
            marshalString(arg.def));
    }

    inline Toggle^ CustomForm::_Marshal(const ::Form::Toggle& arg)
    {
        return gcnew Toggle(
            marshalString(arg.name),
            marshalString(arg.title),
            arg.def);
    }

    inline Slider^ CustomForm::_Marshal(const ::Form::Slider& arg)
    {
        return gcnew Slider(
            marshalString(arg.name),
            marshalString(arg.title),
            arg.minValue,
            arg.maxValue,
            arg.step,
            arg.def);
    }

    inline Dropdown^ CustomForm::_Marshal(const ::Form::Dropdown& arg)
    {
        auto dropdownSysList = gcnew List<String^>(static_cast<int>(arg.options.size()));

        for each (auto& var in arg.options)
            dropdownSysList->Add(marshalString(var));

        return gcnew Dropdown(
            marshalString(arg.name),
            marshalString(arg.title),
            dropdownSysList,
            arg.def);
    }

    inline StepSlider^ CustomForm::_Marshal(const ::Form::StepSlider& arg)
    {
        auto stepsliderSysList = gcnew List<String^>(static_cast<int>(arg.options.size()));

        for each (auto& var in arg.options)
            stepsliderSysList->Add(marshalString(var));

        return gcnew StepSlider(
            marshalString(arg.name),
            marshalString(arg.title),
            stepsliderSysList,
            arg.def);
    }
} // namespace LiteLoader::Form
