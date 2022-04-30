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

private:
    String ^ text, ^image;
    ButtonCallback ^ callback;


public:
    property String ^ Text {
        String ^ get() {
            return text;
        };
        void set(String ^ value)
        {
            text = value;
        }
    };
    property String ^ Image {
        String ^ get() {
            return image;
        };
        void set(String ^ value)
        {
            image = value;
        }
    };
    property ButtonCallback ^ Callback {
        ButtonCallback ^ get() {
            return callback;
        };
        void set(ButtonCallback ^ value)
        {
            callback = value;
        }
    };

public:
    inline Button(String ^ text, String ^ image, ButtonCallback ^ callback);
    inline Button(String ^ text, String ^ image);
    inline Button(String ^ text);
    inline ~Button();
    inline void SetText(String ^ _text);
    inline void SetImage(String ^ _image);
    inline void SetCallback(ButtonCallback ^ _callback);

private:
    delegate void delButtonCallback(::Player*);
    typedef void (*pButtonCallback)(::Player*);
    void NATIVECALLBACK CallbackFn(::Player* p);
    GCHandle gch;

public:
    pButtonCallback ToNativeCallback();
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

private:
    String ^ name;
    String ^ value;
    Type type{};

public:
    property String ^ Name {
        String ^ get() {
            return name;
        };
        void set(String ^ value)
        {
            name = value;
        }
    };
    property String ^ Value {
        String ^ get() {
            return value;
        };
        void set(String ^ value)
        {
            value = value;
        }
    };
    property Type ElementType
    {
        Type get()
        {
            return type;
        };
        void set(Type value)
        {
            type = value;
        }
    };

    inline void SetName(String ^ _name);
    inline virtual Type GetType() abstract = 0;
    inline String ^ GetString();
    inline int GetNumber();
    inline bool GetBool();
};

public
ref class Label : public CustomFormElement
{
private:
    String ^ text;

public:
    property String ^ Text {
        String ^ get() {
            return text;
        };
        void set(String ^ value)
        {
            text = value;
        }
    };


public:
    inline Label(String ^ name, String ^ text);
    inline Type GetType() override;
    inline void SetText(String ^ _text);
};

public
ref class Input : public CustomFormElement
{
private:
    String ^ title, ^placeholder, ^def, ^data;

public:
    property String ^ Title {
        String ^ get() {
            return title;
        };
        void set(String ^ value)
        {
            title = value;
        }
    };
    property String ^ Placeholder {
        String ^ get() {
            return placeholder;
        };
        void set(String ^ value)
        {
            placeholder = value;
        }
    };
    property String ^ Def {
        String ^ get() {
            return def;
        };
        void set(String ^ value)
        {
            def = value;
        }
    };
    property String ^ Data {
        String ^ get() {
            return data;
        };
        void set(String ^ value)
        {
            data = value;
        }
    };

    inline Input(String ^ name, String ^ title, String ^ placeholder, String ^ def);
    inline Input(String ^ name, String ^ title, String ^ placeholder);
    inline Input(String ^ name, String ^ title);
    inline Type GetType() override;
    inline void SetTitle(String ^ _title);
    inline void SetPlaceHolder(String ^ _placeholder);
    inline void SetDefault(String ^ _def);
};

public
ref class Toggle : public CustomFormElement
{
private:
    using DataType = bool;
    String ^ title;
    bool def, data;

public:
    property String ^ Title {
        String ^ get() {
            return title;
        };
        void set(String ^ value)
        {
            title = value;
        }
    };
    property bool Def
    {
        bool get()
        {
            return def;
        };
        void set(bool value)
        {
            def = value;
        }
    };
    property bool Data
    {
        bool get()
        {
            return data;
        };
        void set(bool value)
        {
            data = value;
        }
    };

public:
    inline Toggle(String ^ name, String ^ title, bool def);
    inline Toggle(String ^ name, String ^ title);
    inline Type GetType() override;
    inline void SetTitle(String ^ _title);
    inline void SetDefault(bool _def);
};

public
ref class Dropdown : public CustomFormElement
{
private:
    String ^ title;
    List<String ^> ^ options;
    int def, data{};

public:
    property String ^ Title {
        String ^ get() {
            return title;
        };
        void set(String ^ value)
        {
            title = value;
        }
    };
    property List<String ^> ^ Options {
        List<String ^> ^ get() {
            return options;
        };
        void set(List<String ^> ^ value)
        {
            options = value;
        }
    };
    property int Def
    {
        int get()
        {
            return def;
        };
        void set(int value)
        {
            def = value;
        }
    };
    property int Data
    {
        int get()
        {
            return data;
        };
        void set(int value)
        {
            data = value;
        }
    };

public:
    inline Dropdown(String ^ name, String ^ title, List<String ^> ^ options, int defId);
    inline Dropdown(String ^ name, String ^ title, List<String ^> ^ options);
    inline Type GetType() override;
    inline void SetTitle(String ^ _title);
    inline void SetOptions(List<String ^> ^ _options);
    inline void AddOption(String ^ option);
    inline void SetDefault(int defId);
};

public
ref class Slider : public CustomFormElement
{
private:
    String ^ title;
    int min, max, step, def, data{};

public:
    property String ^ Title {
        String ^ get() {
            return title;
        };
        void set(String ^ value)
        {
            title = value;
        }
    };
    property int Min
    {
        int get()
        {
            return min;
        };
        void set(int value)
        {
            min = value;
        }
    };
    property int Max
    {
        int get()
        {
            return max;
        };
        void set(int value)
        {
            max = value;
        }
    };
    property int Step
    {
        int get()
        {
            return step;
        };
        void set(int value)
        {
            step = value;
        }
    };
    property int Def
    {
        int get()
        {
            return def;
        };
        void set(int value)
        {
            def = value;
        }
    };
    property int Data
    {
        int get()
        {
            return data;
        };
        void set(int value)
        {
            data = value;
        }
    };

public:
    inline Slider(String ^ name, String ^ title, int min, int max, int step, int def);
    inline Slider(String ^ name, String ^ title, int min, int max, int step);
    inline Slider(String ^ name, String ^ title, int min, int max);
    inline Type GetType() override;
    inline void SetTitle(String ^ _title);
    inline void SetMin(int _min);
    inline void SetMax(int _max);
    inline void SetStep(int _step);
    inline void SetDefault(int _def);
};

public
ref class StepSlider : public CustomFormElement
{
private:
    String ^ title;
    List<String ^> ^ options;
    int def, data{};

public:
    property String ^ Title {
        String ^ get() {
            return title;
        };
        void set(String ^ value)
        {
            title = value;
        }
    };
    property List<String ^> ^ Options {
        List<String ^> ^ get() {
            return options;
        };
        void set(List<String ^> ^ value)
        {
            options = value;
        }
    };
    property int Def
    {
        int get()
        {
            return def;
        };
        void set(int value)
        {
            def = value;
        }
    };
    property int Data
    {
        int get()
        {
            return data;
        };
        void set(int value)
        {
            data = value;
        }
    };

public:
    inline StepSlider(String ^ name, String ^ title, List<String ^> ^ options, int defId);
    inline StepSlider(String ^ name, String ^ title, List<String ^> ^ options);
    inline Type GetType() override;
    inline void SetTitle(String ^ _title);
    inline void SetOptions(List<String ^> ^ _options);
    inline void AddOption(String ^ option);
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
    String ^ title, ^content;
    List<SimpleFormElement ^> ^ elements;
    Callback ^ callback;

public:
    SimpleForm(String ^ title, String ^ content);
    ~SimpleForm();
    inline SimpleForm ^ SetTitle(String ^ title);
    inline SimpleForm ^ CstContent(String ^ content);
    inline SimpleForm ^ AddButton(String ^ text, String ^ image, Button::ButtonCallback ^ callback);
    inline SimpleForm ^ AddButton(String ^ text, String ^ image);
    inline SimpleForm ^ AddButton(String ^ text);
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
    using kvPair = Pair<String ^, CustomFormElement ^>;

public:
    delegate void Callback(MC::Player ^, Dictionary<String ^, CustomFormElement ^> ^);
    String ^ title;
    List<kvPair> ^ elements;
    Callback ^ callback = nullptr;

public:
    CustomForm(String ^ title);
    ~CustomForm();

    inline CustomForm ^ append(CustomFormElement ^ element);

private:
    delegate void de_sendFunc(::Player*, std::map<string, std::shared_ptr<::Form::CustomFormElement>>);
    void NATIVECALLBACK sendFunc(::Player* p, std::map<string, std::shared_ptr<::Form::CustomFormElement>> arg);
    ::Form::CustomForm* GenerateNativeForm();
    ::Form::CustomForm* nativeform = nullptr;
    Dictionary<String ^, CustomFormElement ^> ^ CallbackDictionary = nullptr;
    bool isFormGenerated = false;
    bool isDictionaryGenerated = false;
    List<GCHandle> ^ gchList;

public:
    bool SendTo(MC::Player ^ player, Callback ^ callback);
    inline bool SendTo(MC::Player ^ player);

    inline CustomFormElement::Type GetType(int index);

    inline String ^ GetString(String const ^ name);
    inline int GetNumber(String const ^ name);
    inline bool GetBool(String const ^ name);
    inline String ^ GetString(int index);
    inline int GetNumber(int index);
    inline bool GetBool(int index);

    inline void SetValue(int index, String ^ value);
};
} // namespace LLNET::Form