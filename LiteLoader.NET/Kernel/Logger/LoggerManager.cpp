#pragma unmanaged
#include <LiteLoader.NET/Header/Logger/LoggerManager.hpp>
#include <LoggerAPI.h>

#pragma unmanaged
Logger LoggerManager::defaultLogger = Logger("");
#pragma unmanaged
std::unordered_map<LoggerID, std::pair<RefCount, std::unique_ptr<::Logger>>> LoggerManager::LoggerData = {};
#pragma unmanaged
std::tuple<LoggerManager::IsDeleted, LoggerID, Logger*>  LoggerManager::OperatingLogger = { true,0,nullptr };
#pragma unmanaged
std::pair<LoggerID, bool> LoggerManager::CreateLogger(const std::string str)
{
	LoggerID id = do_hash(str.c_str());
	auto& a = LoggerData.insert(std::make_pair(id, std::pair<RefCount, std::unique_ptr<::Logger>>(1, new Logger(str))));
	OperatingLogger = { false,id,a.first->second.second.get() };
	return std::make_pair(id, a.second);
}
#pragma unmanaged
void LoggerManager::WriteLine(LoggerID id, OutputStreamType t, const std::wstring& wstr)
{
	::Logger::OutputStream* pstream = nullptr;
	::Logger* plogger = nullptr;

	//Optimizing
	if (!std::get<0>(OperatingLogger) && id == std::get<1>(OperatingLogger))
	{
		plogger = std::get<2>(OperatingLogger);
		goto jmp;
	}

	{
		auto iter = LoggerData.find(id);
		if (iter != LoggerData.end())
			plogger = iter->second.second.get();
		else
			plogger = &defaultLogger;
		OperatingLogger = { false,id,plogger };
	}

jmp:

	switch (t)
	{
	case LoggerManager::OutputStreamType::debug:
		pstream = &plogger->debug;
		break;
	case LoggerManager::OutputStreamType::info:
		pstream = &plogger->info;
		break;
	case LoggerManager::OutputStreamType::warn:
		pstream = &plogger->warn;
		break;
	case LoggerManager::OutputStreamType::error:
		pstream = &plogger->error;
		break;
	case LoggerManager::OutputStreamType::fatal:
		pstream = &plogger->fatal;
		break;
	default:
		break;
	}

	(*pstream)(TextEncoding::fromUnicode(wstr));
}
#pragma unmanaged
void LoggerManager::WriteLine(OutputStreamType t, const std::string& str)
{
	::Logger::OutputStream* pstream = nullptr;
	switch (t)
	{
	case LoggerManager::OutputStreamType::debug:
		pstream = &defaultLogger.debug;
		break;
	case LoggerManager::OutputStreamType::info:
		pstream = &defaultLogger.info;
		break;
	case LoggerManager::OutputStreamType::warn:
		pstream = &defaultLogger.warn;
		break;
	case LoggerManager::OutputStreamType::error:
		pstream = &defaultLogger.error;
		break;
	case LoggerManager::OutputStreamType::fatal:
		pstream = &defaultLogger.fatal;
		break;
	default:
		break;
	}
	(*pstream)(str);
}
#pragma unmanaged
void LoggerManager::WriteLine(OutputStreamType t, const std::string str, nullptr_t)
{
	LoggerManager::WriteLine(t, str);
}
#pragma unmanaged
void LoggerManager::DeleteLogger(LoggerID id)
{
	auto iter = LoggerData.find(id);
	if (iter != LoggerData.end())
	{
		--(iter->second.first);
		if (!iter->second.first)//iter->second.first==0
		{
			LoggerData.erase(iter);
		}
	}
	if (!std::get<0>(OperatingLogger) && id == std::get<1>(OperatingLogger))
		OperatingLogger = { true,0,nullptr };
}

#pragma unmanaged
void LoggerManager::tryLock(LoggerID id)
{
	::Logger* plogger = nullptr;
	if (!std::get<0>(OperatingLogger) && id == std::get<1>(OperatingLogger))
	{
		plogger = std::get<2>(OperatingLogger);
		goto jmp;
	}

	{
		auto iter = LoggerData.find(id);
		if (iter != LoggerData.end())
			plogger = iter->second.second.get();
		else
			return;
	}

jmp:

	plogger->tryLock();
}
#pragma unmanaged
void LoggerManager::lock(LoggerID id)
{
	::Logger* plogger = nullptr;
	if (!std::get<0>(OperatingLogger) && id == std::get<1>(OperatingLogger))
	{
		plogger = std::get<2>(OperatingLogger);
		goto jmp;
	}

	{
		auto iter = LoggerData.find(id);
		if (iter != LoggerData.end())
			plogger = iter->second.second.get();
		else
			return;
	}

jmp:

	plogger->lock();
}
#pragma unmanaged
void LoggerManager::unlock(LoggerID id)
{
	::Logger* plogger = nullptr;
	if (!std::get<0>(OperatingLogger) && id == std::get<1>(OperatingLogger))
	{
		plogger = std::get<2>(OperatingLogger);
		goto jmp;
	}

	{
		auto iter = LoggerData.find(id);
		if (iter != LoggerData.end())
			plogger = iter->second.second.get();
		else
			return;
	}

jmp:

	plogger->unlock();
}
#pragma unmanaged
void LoggerManager::setDefaultFile(const std::string& logFile, bool appendMode)
{
	::Logger::setDefaultFile(logFile, appendMode);
}
#pragma unmanaged
void LoggerManager::setDefaultFile(std::nullptr_t a0)
{
	::Logger::setDefaultFile(a0);
}
#pragma unmanaged
bool LoggerManager::setFile(LoggerID id, const std::string& logFile, bool appendMode)
{
	::Logger* plogger = nullptr;
	if (!std::get<0>(OperatingLogger) && id == std::get<1>(OperatingLogger))
	{
		plogger = std::get<2>(OperatingLogger);
		goto jmp;
	}

	{
		auto iter = LoggerData.find(id);
		if (iter != LoggerData.end())
			plogger = iter->second.second.get();
		else
			return false;
	}

jmp:
	return plogger->setFile(logFile, appendMode);
}

bool LoggerManager::setFile(LoggerID id, nullptr_t)
{
	::Logger* plogger = nullptr;
	if (!std::get<0>(OperatingLogger) && id == std::get<1>(OperatingLogger))
	{
		plogger = std::get<2>(OperatingLogger);
		goto jmp;
	}

	{
		auto iter = LoggerData.find(id);
		if (iter != LoggerData.end())
			plogger = iter->second.second.get();
		else
			return false;
	}


jmp:
	return plogger->setFile(nullptr);
}

std::string LoggerManager::GetTitle(LoggerID id)
{
	::Logger* plogger = nullptr;
	if (!std::get<0>(OperatingLogger) && id == std::get<1>(OperatingLogger))
	{
		plogger = std::get<2>(OperatingLogger);
		goto jmp;
	}

	{
		auto iter = LoggerData.find(id);
		if (iter != LoggerData.end())
			plogger = iter->second.second.get();
		else
			return std::string("");
	}

jmp:
	return plogger->title;
}

void LoggerManager::SetTitle(LoggerID id, const std::string& _title)
{
	::Logger* plogger = nullptr;
	if (!std::get<0>(OperatingLogger) && id == std::get<1>(OperatingLogger))
	{
		plogger = std::get<2>(OperatingLogger);
		goto jmp;
	}

	{
		auto iter = LoggerData.find(id);
		if (iter != LoggerData.end())
			plogger = iter->second.second.get();
		else
			return;
	}

jmp:

	plogger->title = _title;
}