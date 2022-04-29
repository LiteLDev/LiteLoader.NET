#pragma once
#include <FormUI.h>
#include "MC/ServerPlayer.hpp"
#include "MC/Player.hpp"

#include <MC/RedStoneWireBlock.hpp>

//#define DEBUG

using System::Collections::Generic::Dictionary;
using System::Collections::Generic::List;

namespace LLNET::Form
{
//////////////////////////////// Simple Form Elements ////////////////////////////////
public
ref class SimpleFormElement
{
};

public
ref class Button : public SimpleFormElement
{
public:
    delegate void ButtonCallback(MC::Player ^);
    System::String ^ text, ^image;
    ButtonCallback ^ callback;

public:
    inline Button(System::String ^ text, System::String ^ image, ButtonCallback ^ callback);
    inline Button(System::String ^ text, System::String ^ image);
    inline Button(System::String ^ text);
    inline ~Button();
    inline void SetText(System::String ^ _text);
    inline void SetImage(System::String ^ _image);
    inline void SetCallback(ButtonCallback ^ _callback);

private:
    delegate void _ButtonCallback(::Player*);
    typedef void (*NativeCallback)(::Player*);
    void NATIVECALLBACK callbackfunc(::Player* p);
    GCHandle gch;

public:
    NativeCallback ToNativeCallback();
};

//////////////////////////////// Custom Form Elements ////////////////////////////////

public
ref class CustomFormElement abstract
{
public:
    enum class Type
    {
        Label,
        Input,
        Toggle,
        Dropdown,
        Slider,
        StepSlider
    };
    System::String ^ name;
    System::String ^ value;
    Type type{};
    inline void SetName(System::String ^ _name);
    inline virtual Type GetType() abstract = 0;
    inline System::String ^ GetString();
    inline int GetNumber();
    inline bool GetBool();
};

public
ref class Label : public CustomFormElement
{
public:
    System::String ^ text;

public:
    inline Label(System::String ^ name, System::String ^ text);
    inline Type GetType() override;
    inline void SetText(System::String ^ _text);
};

public
ref class Input : public CustomFormElement
{
public:
    System::String ^ title, ^placeholder, ^def, ^data;
    inline Input(System::String ^ name, System::String ^ title, System::String ^ placeholder, System::String ^ def);
    inline Input(System::String ^ name, System::String ^ title, System::String ^ placeholder);
    inline Input(System::String ^ name, System::String ^ title);
    inline Type GetType() override;
    inline void SetTitle(System::String ^ _title);
    inline void SetPlaceHolder(System::String ^ _placeholder);
    inline void SetDefault(System::String ^ _def);
};

public
ref class Toggle : public CustomFormElement
{
public:
    using DataType = bool;
    System::String ^ title;
    bool def, data;

public:
    inline Toggle(System::String ^ name, System::String ^ title, bool def);
    inline Toggle(System::String ^ name, System::String ^ title);
    inline Type GetType() override;
    inline void SetTitle(System::String ^ _title);
    inline void SetDefault(bool _def);
};

public
ref class Dropdown : public CustomFormElement
{
public:
    System::String ^ title;
    List<System::String ^> ^ options;
    int def, data{};

public:
    inline Dropdown(System::String ^ name, System::String ^ title, List<System::String ^> ^ options, int defId);
    inline Dropdown(System::String ^ name, System::String ^ title, List<System::String ^> ^ options);
    inline Type GetType() override;
    inline void SetTitle(System::String ^ _title);
    inline void SetOptions(List<System::String ^> ^ _options);
    inline void AddOption(System::String ^ option);
    inline void SetDefault(int defId);
};

public
ref class Slider : public CustomFormElement
{
public:
    System::String ^ title;
    int min, max, step, def, data{};

public:
    inline Slider(System::String ^ name, System::String ^ title, int min, int max, int step, int def);
    inline Slider(System::String ^ name, System::String ^ title, int min, int max, int step);
    inline Slider(System::String ^ name, System::String ^ title, int min, int max);
    inline Type GetType() override;
    inline void SetTitle(System::String ^ _title);
    inline void SetMin(int _min);
    inline void SetMax(int _max);
    inline void SetStep(int _step);
    inline void SetDefault(int _def);
};

public
ref class StepSlider : public CustomFormElement
{
public:
    System::String ^ title;
    List<System::String ^> ^ options;
    int def, data{};

public:
    inline StepSlider(System::String ^ name, System::String ^ title, List<System::String ^> ^ options, int defId);
    inline StepSlider(System::String ^ name, System::String ^ title, List<System::String ^> ^ options);
    inline Type GetType() override;
    inline void SetTitle(System::String ^ _title);
    inline void SetOptions(List<System::String ^> ^ _options);
    inline void AddOption(System::String ^ option);
    inline void SetDefault(int defId);
};

//////////////////////////////// Forms ////////////////////////////////

public
ref class FormImpl
{
};

public
ref class SimpleForm : public FormImpl
{
public:
    delegate void Callback(MC::Player ^, int);
    System::String ^ title, ^content;
    List<SimpleFormElement ^> ^ elements;
    Callback ^ callback;

public:
    SimpleForm(System::String ^ title, System::String ^ content);
    ~SimpleForm();
    inline SimpleForm ^ SetTitle(System::String ^ title);
    inline SimpleForm ^ CstContent(System::String ^ content);
    inline SimpleForm ^ AddButton(System::String ^ text, System::String ^ image, Button::ButtonCallback ^ callback);
    inline SimpleForm ^ AddButton(System::String ^ text, System::String ^ image);
    inline SimpleForm ^ AddButton(System::String ^ text);
    inline SimpleForm ^ Append(Button ^ element);
    bool SendTo(MC::Player ^ _player, Callback ^ _callback);
    bool SendTo(MC::Player ^ player);

private:
    delegate void _Callback(::Player*, int);
    void NATIVECALLBACK sendToFunc(::Player* p, int a);
    List<GCHandle> ^ gchList;
};


public
ref class CustomForm : public FormImpl
{
    using kvPair = Pair<System::String ^, CustomFormElement ^>;

public:
    delegate void Callback(MC::Player ^, Dictionary<System::String ^, CustomFormElement ^> ^);
    System::String ^ title;
    List<kvPair> ^ elements;
    Callback ^ callback = nullptr;

public:
    CustomForm(System::String ^ title);
    ~CustomForm();

    inline CustomForm ^ append(CustomFormElement ^ element);

private:
    delegate void de_sendFunc(::Player*, std::map<string, std::shared_ptr<::Form::CustomFormElement>>);
    void NATIVECALLBACK sendFunc(::Player* p, std::map<string, std::shared_ptr<::Form::CustomFormElement>> arg);
    ::Form::CustomForm* GenerateNativeForm();
    ::Form::CustomForm* nativeform = nullptr;
    Dictionary<System::String ^, CustomFormElement ^> ^ CallbackDictionary = nullptr;
    bool isFormGenerated = false;
    bool isDictionaryGenerated = false;
    List<GCHandle> ^ gchList;

public:
    bool sendTo(MC::Player ^ player, Callback ^ callback);
    inline bool sendTo(MC::Player ^ player);

    inline CustomFormElement::Type GetType(int index);

    inline System::String ^ GetString(System::String const ^ name);
    inline int GetNumber(System::String const ^ name);
    inline bool GetBool(System::String const ^ name);
    inline System::String ^ GetString(int index);
    inline int GetNumber(int index);
    inline bool GetBool(int index);

    inline void SetValue(int index, System::String ^ value);
};
} // namespace LLNET::Form