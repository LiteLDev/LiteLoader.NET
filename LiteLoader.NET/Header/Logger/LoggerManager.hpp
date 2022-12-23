#pragma once
#pragma unmanaged

#include <stdint.h>
#include <string>
#include <unordered_map>
#include <memory>

class Logger;

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

    static void SetTitle(LoggerID id, const std::string& _title);
    static std::string GetTitle(LoggerID id);


    static void tryLock(LoggerID id);
    static void lock(LoggerID id);
    static void unlock(LoggerID id);
    static void setDefaultFile(const std::string& logFile, bool appendMode);
    static void setDefaultFile(std::nullptr_t a0);
    //static void endl(OutputStream& o);

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