#pragma once
#pragma unmanaged
#include <LoggerAPI.h>
#include <initializer_list>
#include <Utils/Hash.h>

using LoggerID = uint64_t;

using RefCount = size_t;

class LoggerManager
{
public:
	LoggerManager() = delete;
public:
	enum class OutputStreamType {
		debug = 0,
		info = 1,
		warn = 2,
		error = 3,
		fatal = 4
	};
public:

	static std::pair<LoggerID, bool> CreateLogger(const std::string str);
	static void DeleteLogger(LoggerID id);

	inline static void SetTitle(LoggerID id, const std::string& _title);
	inline static std::string GetTitle(LoggerID id);


	inline static void tryLock(LoggerID id);
	inline static void lock(LoggerID id);
	inline static void unlock(LoggerID id);
	inline static void setDefaultFile(const std::string& logFile, bool appendMode);
	inline static void setDefaultFile(std::nullptr_t a0);
	//inline static void endl(OutputStream& o);

	static bool setFile(LoggerID id, const std::string& logFile, bool appendMode = true);
	static bool setFile(LoggerID id, nullptr_t);

	static void WriteLine(LoggerID id, OutputStreamType t, const std::wstring& wstr);
	static void WriteLine(OutputStreamType t, const std::string& str);
	static void WriteLine(OutputStreamType t, const std::string str, nullptr_t);
private:
	typedef bool IsDeleted;
	static std::tuple<IsDeleted, LoggerID, Logger*>  OperatingLogger;
	static ::Logger defaultLogger;
	static std::unordered_map<LoggerID, std::pair<RefCount, std::unique_ptr<::Logger>>> LoggerData;
};



#pragma managed
#include <LiteLoader.NET/Main/.NETGlobal.hpp>
namespace LLNET::Logger {
	public ref class Logger {
	public:
		value class ENDLINE {};
		static ENDLINE Endl;
		ENDLINE endl;
	private:
		enum class OutputStreamType
		{
			debug = 0,
			info = 1,
			warn = 2,
			error = 3,
			fatal = 4
		};
	public:
		ref class OutputStream {
		public:
			OutputStream(OutputStreamType t, LoggerID loggerid);
			void WriteLine(System::String^ string);
			void WriteLine(System::Object^ obj);
			void WriteLine(System::String^ format, ...array<Object^>^ args);
			inline static OutputStream^ operator<<(OutputStream^ os, System::Boolean val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::Byte val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::SByte val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::Char val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::Int16 val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::UInt16 val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::Int32 val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::UInt32 val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::Int64 val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::UInt64 val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::Single val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::Double val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::String^ val);
			inline static OutputStream^ operator<<(OutputStream^ os, System::Object^ val);
			inline static OutputStream^ operator<<(OutputStream^ os, ENDLINE endl);
		private:
			LoggerID loggerid;
			OutputStreamType type;
			List<System::Object^>^ buffer;
		};
	public:
		Logger(System::String^ title);
		Logger();
		~Logger();

		OutputStream^ debug;
		OutputStream^ info;
		OutputStream^ warn;
		OutputStream^ error;
		OutputStream^ fatal;

		property OutputStream^ Debug {OutputStream^ get() { return debug; }};
		property OutputStream^ Info {OutputStream^ get() { return info; }};
		property OutputStream^ Warn {OutputStream^ get() { return warn; }};
		property OutputStream^ Error {OutputStream^ get() { return error; }};
		property OutputStream^ Fatal {OutputStream^ get() { return fatal; }};

		property String^ Title {inline String^ get(); inline void set(String^ _title); }
		//property IntPtr std_ofstream {inline IntPtr get(); inline void set(IntPtr pofs); }
		//property MC::Player^ player {inline MC::Player^ get(); inline void set(MC::Player^ _player); }
		//property int consoleLevel {inline int get(); inline void set(int cleLevel); }
		//property int fileLevel {inline int get(); inline void set(int fLevel); }
		//property int playerLevel {inline int get(); inline void set(int conLevel); }

	private:
		LoggerID id;
	};
}
