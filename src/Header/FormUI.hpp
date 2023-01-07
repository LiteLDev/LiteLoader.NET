#pragma once
#include <FormUI.h>
#include "MC/ServerPlayer.hpp"
#include "MC/Player.hpp"

#include <src/Tools/NativeCallbackConverter.hpp>
#include <src/Main/ClassTemplate.hpp>

//#define DEBUG

using System::Collections::Generic::Dictionary;
using System::Collections::Generic::List;

namespace LiteLoader::Form
{
    ref class CustomForm;

    //////////////////////////////// Simple Form Elements ////////////////////////////////

    public
        ref class SimpleFormElement
    {
    };

    public
        ref class Button : public SimpleFormElement
    {
    public:
        delegate void ButtonCallback(MC::Player^);

        property String^ Text;
        property String^ Image;
        property ButtonCallback^ Callback;

        inline Button(String^ text, String^ image, ButtonCallback^ callback);
        inline Button(String^ text, String^ image);
        inline Button(String^ text);
        inline !Button();
        inline ~Button();

        using pButtonCallback = void(*)(Player*);
        pButtonCallback ToNativeCallback();

    private:
        List<NativeCallbackHandler^>^ handlers = gcnew List<NativeCallbackHandler^>;
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

        property String^ Name;
        property String^ Value;
        property Type ElementType { virtual Type get() abstract; }

        inline String^ GetString();
        inline int GetInt();
        inline float GetFloat();
        inline double GetDouble();
        inline bool GetBool();

    internal:
        List<CustomForm^>^ appendedForms = gcnew List<CustomForm^>;
        void reSetGeneratedForm();
    };

    public
        ref class Label : public CustomFormElement
    {
        String^ text;

    public:
        property String^ Text
        {
            String^ get()
            {
                return text;
            };

            void set(String^ value)
            {
                text = value;
                reSetGeneratedForm();
            }
        };

        property Type ElementType
        {
            virtual Type get() override { return Type::Label; }
        }

        inline Label(String^ name, String^ text);
    };

    public
        ref class Input : public CustomFormElement
    {
        String ^title, ^placeholder, ^def;

    public:
        property String^ Title
        {
            String^ get()
            {
                return title;
            };

            void set(String^ value)
            {
                title = value;
                reSetGeneratedForm();
            }
        };

        property String^ Placeholder
        {
            String^ get()
            {
                return placeholder;
            };

            void set(String^ value)
            {
                placeholder = value;
                reSetGeneratedForm();
            }
        };

        property String^ Def
        {
            String^ get()
            {
                return def;
            };

            void set(String^ value)
            {
                def = value;
                reSetGeneratedForm();
            }
        };

        property Type ElementType
        {
            virtual Type get() override { return Type::Input; }
        }

        inline Input(String^ name, String^ title, String^ placeholder, String^ def);
        inline Input(String^ name, String^ title, String^ placeholder);
        inline Input(String^ name, String^ title);
    };

    public
        ref class Toggle : public CustomFormElement
    {
        String^ title;
        bool def;

    public:
        property String^ Title
        {
            String^ get()
            {
                return title;
            };

            void set(String^ value)
            {
                title = value;
                reSetGeneratedForm();
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
                reSetGeneratedForm();
            }
        };

        property Type ElementType
        {
            virtual Type get() override { return Type::Toggle; }
        }

        inline Toggle(String^ name, String^ title, bool def);
        inline Toggle(String^ name, String^ title);
    };

    public
        ref class Dropdown : public CustomFormElement
    {
        String^ title;
        List<String^>^ options;
        int def;

    public:
        property String^ Title
        {
            String^ get()
            {
                return title;
            };

            void set(String^ value)
            {
                title = value;
                reSetGeneratedForm();
            }
        };

        property List<String^>^ Options
        {
            List<String^>^ get()
            {
                return options;
            };

            void set(List<String^>^ value)
            {
                options = value;
                reSetGeneratedForm();
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
                reSetGeneratedForm();
            }
        };

        property Type ElementType
        {
            virtual Type get() override { return Type::Dropdown; }
        }

        inline Dropdown(String^ name, String^ title, List<String^>^ options, int defId);
        inline Dropdown(String^ name, String^ title, List<String^>^ options);
        inline void AddOption(String^ option);
    };

    public
        ref class Slider : public CustomFormElement
    {
        String^ title;
        double min, max, step, def;

    public:
        property String^ Title
        {
            String^ get()
            {
                return title;
            };

            void set(String^ value)
            {
                title = value;
                reSetGeneratedForm();
            }
        };

        property double Min
        {
            double get()
            {
                return min;
            };

            void set(double value)
            {
                min = value;
                reSetGeneratedForm();
            }
        };

        property double Max
        {
            double get()
            {
                return max;
            };

            void set(double value)
            {
                max = value;
                reSetGeneratedForm();
            }
        };

        property double Step
        {
            double get()
            {
                return step;
            };

            void set(double value)
            {
                step = value;
                reSetGeneratedForm();
            }
        };

        property double Def
        {
            double get()
            {
                return def;
            };

            void set(double value)
            {
                def = value;
                reSetGeneratedForm();
            }
        };

        property Type ElementType
        {
            virtual Type get() override { return Type::Slider; }
        }

        inline Slider(String^ name, String^ title, double min, double max, double step, double def);
        inline Slider(String^ name, String^ title, double min, double max, double step);
        inline Slider(String^ name, String^ title, double min, double max);
    };

    public
        ref class StepSlider : public CustomFormElement
    {
        String^ title;
        List<String^>^ options;
        int def;

    public:
        property String^ Title
        {
            String^ get()
            {
                return title;
            };

            void set(String^ value)
            {
                title = value;
                reSetGeneratedForm();
            }
        };

        property List<String^>^ Options
        {
            List<String^>^ get()
            {
                return options;
            };

            void set(List<String^>^ value)
            {
                options = value;
                reSetGeneratedForm();
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
                reSetGeneratedForm();
            }
        };

        property Type ElementType
        {
            virtual Type get() override { return Type::StepSlider; }
        }

        inline StepSlider(String^ name, String^ title, List<String^>^ options, int defId);
        inline StepSlider(String^ name, String^ title, List<String^>^ options);
        inline void AddOption(String^ option);
    };

    //////////////////////////////// Forms ////////////////////////////////

    public
        interface class FormImpl
    {
    };

    public
        ref class SimpleForm : public ClassTemplate<SimpleForm, ::Form::SimpleForm>, public FormImpl
    {
    public:
        delegate void SimpleFormCallback(MC::Player^, int);

        property String^ Title;
        property String^ Content;
        property List<SimpleFormElement^>^ Elements;
        property SimpleFormCallback^ Callback;

        SimpleForm(String^ title, String^ content);
        !SimpleForm();
        ~SimpleForm();

        inline SimpleForm^ AddButton(String^ text, String^ image, Button::ButtonCallback^ callback);
        inline SimpleForm^ AddButton(String^ text, String^ image);
        inline SimpleForm^ AddButton(String^ text);
        inline SimpleForm^ Append(Button^ element);
        bool SendTo(MC::Player^ player, SimpleFormCallback^ callback);
        bool SendTo(MC::Player^ player);

    private:
        List<NativeCallbackHandler^>^ handlers = gcnew List<NativeCallbackHandler^>;
    };


    public
        ref class ModalForm : public ClassTemplate<ModalForm, ::Form::ModalForm>, public FormImpl
    {
    public:
        delegate void ModalFormCallback(MC::Player^ player, bool isConfirm);

        property String^ Title;
        property String^ Content;
        property String^ ConfirmButton;
        property String^ CancelButton;
        property ModalFormCallback^ Callback;

        ModalForm(String^ title, String^ content, String^ confirmButton, String^ cancelButton);
        !ModalForm();
        ~ModalForm();

        bool SendTo(MC::Player^ player, ModalFormCallback^ callback);
        bool SendTo(MC::Player^ player);

    private:
        List<NativeCallbackHandler^>^ handlers = gcnew List<NativeCallbackHandler^>;
    };


    public
        ref class CustomForm : public ClassTemplate<CustomForm, ::Form::CustomForm>, public FormImpl
    {
        using kvPair = VALUE_TUPLE<String^, CustomFormElement^>;
        List<kvPair>^ elements = gcnew List<kvPair>;

    public:
        delegate void CustomFormCallback(MC::Player^, Dictionary<String^, CustomFormElement^>^);

        property String^ Title;
        property CustomFormCallback^ Callback;

        property List<kvPair>^ Elements
        {
            List<kvPair>^ get()
            {
                return elements;
            };

            void set(List<kvPair>^ value)
            {
                isFormGenerated = false;
                elements = value;
            }
        };

        CustomForm(String^ title);
        !CustomForm();
        ~CustomForm();

        inline CustomForm^ Append(CustomFormElement^ element);
        bool SendTo(MC::Player^ player, CustomFormCallback^ callback);
        inline bool SendTo(MC::Player^ player);
        inline CustomFormElement^ GetElement(const String^ name);
        inline CustomFormElement^ GetElement(int index);

    internal:
        property bool IsFormGenerated;

        static inline ::Form::Label _Marshal(Label^ arg);
        static inline ::Form::Input _Marshal(Input^ arg);
        static inline ::Form::Toggle _Marshal(Toggle^ arg);
        static inline ::Form::Slider _Marshal(Slider^ arg);
        static inline ::Form::Dropdown _Marshal(Dropdown^ arg);
        static inline ::Form::StepSlider _Marshal(StepSlider^ arg);
        static inline Label^ _Marshal(const ::Form::Label& arg);
        static inline Input^ _Marshal(const ::Form::Input& arg);
        static inline Toggle^ _Marshal(const ::Form::Toggle& arg);
        static inline Slider^ _Marshal(const ::Form::Slider& arg);
        static inline Dropdown^ _Marshal(const ::Form::Dropdown& arg);
        static inline StepSlider^ _Marshal(const ::Form::StepSlider& arg);

    private:
        delegate void delSendCallback(Player*, std::map<string, std::shared_ptr<::Form::CustomFormElement>>);
        void NATIVECALLBACK NativeFormSendCallback(
            Player* p, std::map<string, std::shared_ptr<::Form::CustomFormElement>> arg);

        void GenerateNativeForm();
        bool isFormGenerated = false;

        List<NativeCallbackHandler^>^ handlers = gcnew List<NativeCallbackHandler^>;
    };
} // namespace LiteLoader::Form
