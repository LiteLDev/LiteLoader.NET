#pragma once
#include <FormUI.h>
#include "MC/ServerPlayer.hpp"
#include "MC/Player.hpp"

#include "../Tools/NativeCallbackConverter.hpp"
#include "../Main/ClassTemplate.h"

//#define DEBUG

using System::Collections::Generic::Dictionary;
using System::Collections::Generic::List;

namespace LLNET::Form
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

	private:
		String^ text, ^ image;
		ButtonCallback^ callback;


	public:
		property String^ Text {
			String^ get() {
				return text;
			};
			void set(String^ value)
			{
				text = value;
			}
		};
		property String^ Image {
			String^ get() {
				return image;
			};
			void set(String^ value)
			{
				image = value;
			}
		};
		property ButtonCallback^ Callback {
			ButtonCallback^ get() {
				return callback;
			};
			void set(ButtonCallback^ value)
			{
				callback = value;
			}
		};

	public:
		inline Button(String^ text, String^ image, ButtonCallback^ callback);
		inline Button(String^ text, String^ image);
		inline Button(String^ text);
		inline !Button();
		inline ~Button();
		inline void SetText(String^ text);
		inline void SetImage(String^ image);
		inline void SetCallback(ButtonCallback^ callback);

	public:
		typedef void (*pButtonCallback)(::Player*);
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

	private:
		String^ name;
		String^ value;
		Type type;

	public:
		property String^ Name {
			String^ get() {
				return name;
			};
			void set(String^ value)
			{
				name = value;
			}
		};
		property String^ Value {
			String^ get() {
				return value;
			};
			void set(String^ value)
			{
				this->value = value;
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

		inline void SetName(String^ _name);
		inline virtual Type GetElementType() abstract = 0;
		inline String^ GetString();
		inline int GetNumber();
		inline bool GetBool();
	internal:
		List<CustomForm^>^ appendedForms = gcnew List<CustomForm^>;
		void reSetGeneratedForm();
	};

	public
	ref class Label : public CustomFormElement
	{
	private:
		String^ text;

	public:
		property String^ Text {
			String^ get() {
				return text;
			};
			void set(String^ value)
			{
				text = value;
				reSetGeneratedForm();
			}
		};


	public:
		inline Label(String^ name, String^ text);
		inline Type GetElementType() override;
		inline void SetText(String^ _text);
	};

	public
	ref class Input : public CustomFormElement
	{
	private:
		String^ title, ^ placeholder, ^ def;

	public:
		property String^ Title {
			String^ get() {
				return title;
			};
			void set(String^ value)
			{
				title = value;
				reSetGeneratedForm();
			}
		};
		property String^ Placeholder {
			String^ get() {
				return placeholder;
			};
			void set(String^ value)
			{
				placeholder = value;
				reSetGeneratedForm();
			}
		};
		property String^ Def {
			String^ get() {
				return def;
			};
			void set(String^ value)
			{
				def = value;
				reSetGeneratedForm();
			}
		};

		inline Input(String^ name, String^ title, String^ placeholder, String^ def);
		inline Input(String^ name, String^ title, String^ placeholder);
		inline Input(String^ name, String^ title);
		inline Type GetElementType() override;
		inline void SetTitle(String^ title);
		inline void SetPlaceHolder(String^ placeholder);
		inline void SetDefault(String^ def);
	};

	public
	ref class Toggle : public CustomFormElement
	{
	private:
		using DataType = bool;
		String^ title;
		bool def;

	public:
		property String^ Title {
			String^ get() {
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

	public:
		inline Toggle(String^ name, String^ title, bool def);
		inline Toggle(String^ name, String^ title);
		inline Type GetElementType() override;
		inline void SetTitle(String^ title);
		inline void SetDefault(bool def);
	};

	public
	ref class Dropdown : public CustomFormElement
	{
	private:
		String^ title;
		List<String^>^ options;
		int def;

	public:
		property String^ Title {
			String^ get() {
				return title;
			};
			void set(String^ value)
			{
				title = value;
				reSetGeneratedForm();
			}
		};
		property List<String^>^ Options {
			List<String^>^ get() {
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

	public:
		inline Dropdown(String^ name, String^ title, List<String^>^ options, int defId);
		inline Dropdown(String^ name, String^ title, List<String^>^ options);
		inline Type GetElementType() override;
		inline void SetTitle(String^ title);
		inline void SetOptions(List<String^>^ options);
		inline void AddOption(String^ option);
		inline void SetDefault(int defId);
	};

	public
	ref class Slider : public CustomFormElement
	{
	private:
		String^ title;
		int min, max, step, def;

	public:
		property String^ Title {
			String^ get() {
				return title;
			};
			void set(String^ value)
			{
				title = value;
				reSetGeneratedForm();
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
				reSetGeneratedForm();
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
				reSetGeneratedForm();
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

	public:
		inline Slider(String^ name, String^ title, int min, int max, int step, int def);
		inline Slider(String^ name, String^ title, int min, int max, int step);
		inline Slider(String^ name, String^ title, int min, int max);
		inline Type GetElementType() override;
		inline void SetTitle(String^ title);
		inline void SetMin(int min);
		inline void SetMax(int max);
		inline void SetStep(int step);
		inline void SetDefault(int def);
	};

	public
	ref class StepSlider : public CustomFormElement
	{
	private:
		String^ title;
		List<String^>^ options;
		int def;

	public:
		property String^ Title {
			String^ get() {
				return title;
			};
			void set(String^ value)
			{
				title = value;
				reSetGeneratedForm();
			}
		};
		property List<String^>^ Options {
			List<String^>^ get() {
				return options;
			};
			void set(List<String^>^ value)
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
				reSetGeneratedForm();
			}
		};

	public:
		inline StepSlider(String^ name, String^ title, List<String^>^ options, int defId);
		inline StepSlider(String^ name, String^ title, List<String^>^ options);
		inline Type GetElementType() override;
		inline void SetTitle(String^ title);
		inline void SetOptions(List<String^>^ options);
		inline void AddOption(String^ option);
		inline void SetDefault(int defId);
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

	private:
		String^ title, ^ content;
		List<SimpleFormElement^>^ elements = gcnew List<SimpleFormElement^>;
		SimpleFormCallback^ callback;

	public:
		property String^ Title {
			String^ get() {
				return title;
			};
			void set(String^ value)
			{
				title = value;
			}
		};
		property String^ Content {
			String^ get() {
				return content;
			};
			void set(String^ value)
			{
				content = value;
			}
		};
		property List<SimpleFormElement^>^ Elements {
			List<SimpleFormElement^>^ get() {
				return elements;
			};
			void set(List<SimpleFormElement^>^ value)
			{
				elements = value;
			}
		};
		property SimpleFormCallback^ Callback {
			SimpleFormCallback^ get() {
				return callback;
			};
			void set(SimpleFormCallback^ value)
			{
				callback = value;
			}
		};

	public:
		SimpleForm(String^ title, String^ content);
		!SimpleForm();
		~SimpleForm();
		inline SimpleForm^ SetTitle(String^ title);
		inline SimpleForm^ CstContent(String^ content);
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
	ref class CustomForm : public ClassTemplate<CustomForm, ::Form::CustomForm>, public FormImpl
	{
		using kvPair = Pair<String^, CustomFormElement^>;

	public:
		delegate void CustomFormCallback(MC::Player^, Dictionary<String^, CustomFormElement^>^);
		String^ title;
		List<kvPair>^ elements = gcnew List<kvPair>;
		CustomFormCallback^ callback;

	public:
		property String^ Title {
			String^ get() {
				return title;
			};
			void set(String^ value)
			{
				title = value;
			}
		};
		property List<kvPair>^ Elements {
			List<kvPair>^ get() {
				return elements;
			};
			void set(List<kvPair>^ value)
			{
				isFormGenerated = false;
				elements = value;
			}
		};
		property CustomFormCallback^ Callback {
			CustomFormCallback^ get() { return callback; }
			void set(CustomFormCallback^ value) { callback = value; }
		};
	internal:
		property bool IsFormGenerated
		{
			bool get() { return isFormGenerated; }
			void set(bool value) { isFormGenerated = value; }
		}

	public:
		CustomForm(String^ title);
		!CustomForm();
		~CustomForm();

		inline CustomForm^ Append(CustomFormElement^ element);

	private:
		delegate void delSendCallback(::Player*, std::map<string, std::shared_ptr<::Form::CustomFormElement>>);
		void NATIVECALLBACK NativeFormSendCallback(::Player* p, std::map<string, std::shared_ptr<::Form::CustomFormElement>> arg);

		void GenerateNativeForm();
		bool isFormGenerated = false;

		List<NativeCallbackHandler^>^ handlers = gcnew List<NativeCallbackHandler^>;

	public:
		bool SendTo(MC::Player^ player, CustomFormCallback^ callback);
		inline bool SendTo(MC::Player^ player);

		inline CustomFormElement::Type GetElementType(int index);

		inline String^ GetString(String const^ name);
		inline int GetNumber(String const^ name);
		inline bool GetBool(String const^ name);
		inline String^ GetString(int index);
		inline int GetNumber(int index);
		inline bool GetBool(int index);

		inline void SetValue(int index, String^ value);

	internal:
		static inline ::Form::Label _Marshal(Label^ arg);
		static inline ::Form::Input _Marshal(Input^ arg);
		static inline ::Form::Toggle _Marshal(Toggle^ arg);
		static inline ::Form::Slider _Marshal(Slider^ arg);
		static inline ::Form::Dropdown _Marshal(Dropdown^ arg);
		static inline ::Form::StepSlider _Marshal(StepSlider^ arg);
		static inline Label^ _Marshal(::Form::Label const& arg);
		static inline Input^ _Marshal(::Form::Input const& arg);
		static inline Toggle^ _Marshal(::Form::Toggle const& arg);
		static inline Slider^ _Marshal(::Form::Slider const& arg);
		static inline Dropdown^ _Marshal(::Form::Dropdown const& arg);
		static inline StepSlider^ _Marshal(::Form::StepSlider const& arg);
	};
} // namespace LLNET::Form