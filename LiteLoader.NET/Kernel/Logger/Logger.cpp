#include <LiteLoader.NET/Header/Logger/Logger.hpp>
#include <LiteLoader.NET/Header/Logger/LoggerManager.hpp>

#pragma managed
namespace LiteLoader::Logger {
    using msclr::interop::marshal_as;

    Logger::Logger(System::String^ title)
    {
        this->id = LoggerManager::CreateLogger(marshalString(title)).first;
        this->debug = gcnew Logger::OutputStream(OutputStreamType::debug, this->id);
        this->info = gcnew Logger::OutputStream(OutputStreamType::info, this->id);
        this->warn = gcnew Logger::OutputStream(OutputStreamType::warn, this->id);
        this->error = gcnew Logger::OutputStream(OutputStreamType::error, this->id);
        this->fatal = gcnew Logger::OutputStream(OutputStreamType::fatal, this->id);
    }

    Logger::Logger()
    {
        this->id = LoggerManager::CreateLogger("").first;
        this->debug = gcnew Logger::OutputStream(OutputStreamType::debug, this->id);
        this->info = gcnew Logger::OutputStream(OutputStreamType::info, this->id);
        this->warn = gcnew Logger::OutputStream(OutputStreamType::warn, this->id);
        this->error = gcnew Logger::OutputStream(OutputStreamType::error, this->id);
        this->fatal = gcnew Logger::OutputStream(OutputStreamType::fatal, this->id);
    }

    Logger::~Logger()
    {
        LoggerManager::DeleteLogger(this->id);
    }


    Logger::OutputStream::OutputStream(OutputStreamType t, LoggerID loggerid)
        :loggerid(loggerid), type(t), buffer(gcnew List<System::Object^>) {}

    void Logger::OutputStream::WriteLine(System::String^ string)
    {
        LoggerManager::WriteLine(this->loggerid, LoggerManager::OutputStreamType(int(type)), marshalString<CLI_Encoding::E_UTF16>(string));
    }
    void Logger::OutputStream::WriteLine(System::String^ format, ...array<System::Object^>^ args)
    {
        auto str = System::String::Format(format, (array<System::Object^>^)args);
        LoggerManager::WriteLine(this->loggerid, LoggerManager::OutputStreamType(type), marshalString<CLI_Encoding::E_UTF16>(str));
    }
    void Logger::OutputStream::WriteLine(System::Object^ obj) {
        LoggerManager::WriteLine(this->loggerid, LoggerManager::OutputStreamType(type), marshalString<CLI_Encoding::E_UTF16>(obj->ToString()));
    }

    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::Boolean val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::Byte val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::SByte val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::Char val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::Int16 val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::UInt16 val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::Int32 val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::UInt32 val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::Int64 val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::UInt64 val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::Single val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::Double val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::String^ val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, System::Object^ val)
    {
        os->buffer->Add(val);
        return os;
    }
    inline Logger::OutputStream^ Logger::OutputStream::operator<<(OutputStream^ os, ENDLINE endl)
    {
        auto len = os->buffer->Count;

        int ex = 0;
        int _len = len;
        do {
            _len %= 10;
            ex += _len;
        } while (_len > 9);

        auto strbulider = gcnew System::Text::StringBuilder(len * 3 + ex);

        for (int i = 0; i < len; ++i)
        {
            strbulider->Append("{" + i.ToString() + "}");
        }
        try
        {
            os->WriteLine(strbulider->ToString(), os->buffer->ToArray());
        }
        CATCH
            finally
        {
            delete strbulider;
            delete os->buffer;
            os->buffer = gcnew List<System::Object^>;
        }
        return os;
    }

    inline System::String^ Logger::Title::get() {
        return marshalString(LoggerManager::GetTitle(id));
    }

    inline void Logger::Title::set(System::String^ _title) {
        LoggerManager::SetTitle(id, marshalString(_title));
    }

}



