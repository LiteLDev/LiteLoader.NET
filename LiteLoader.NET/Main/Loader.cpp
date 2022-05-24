#include "Loader.hpp"
#include <LoggerAPI.h>
#include ".NETGlobal.hpp"
#include "PluginAttribute.h"

Logger* plogger = nullptr;

System::Reflection::Assembly^ OnAssemblyResolve(System::Object^ sender, System::ResolveEventArgs^ args);

void Init(Logger& logger)
{
	plogger = &logger;
	System::AppDomain::CurrentDomain->AssemblyResolve += gcnew System::ResolveEventHandler(&OnAssemblyResolve);
}

System::Reflection::Assembly^ OnAssemblyResolve(System::Object^ sender, System::ResolveEventArgs^ args) {
	try
	{
		System::Reflection::AssemblyName assemblyName(args->Name);
		if (assemblyName.Name == LLNET_LOADER_NAME)
			return System::Reflection::Assembly::GetExecutingAssembly();

		return System::Reflection::Assembly::LoadFrom(System::IO::Path::Combine(LITELOADER_LIBRARY_DIR, assemblyName.Name + ".dll"));
	}
	catch (System::Exception^ ex)
	{
		plogger->error("Uncaught {} Detected!", marshalString(ex->GetType()->ToString()));
		plogger->error(marshalString(ex->ToString()));
		throw;
	}
	catch (const std::exception& ex)
	{
		plogger->error("Uncaught std::exception Detected!");
		plogger->error(ex.what());
		throw;
	}
	catch (...)
	{
		plogger->error("Uncaught exception Detected!");
		throw;
	}
}

void LoadPlugins(std::vector<std::filesystem::path> const& assemblyPaths, Logger& logger)
{
	size_t count = 0;
	for (auto iter = assemblyPaths.begin(); iter != assemblyPaths.end(); ++iter)
	{
		try
		{
			Assembly::LoadFrom(
				marshalString(iter->string()))
				->GetType(TEXT(LLNET_ENTRY_CLASS))
				->GetMethod(TEXT(LLNET_ENTRY_METHOD))
				->Invoke(nullptr, nullptr);
			logger.info("Plugin <{}> loaded", iter->filename().string());
			++count;
		}
		catch (System::Reflection::TargetInvocationException^ ex)
		{
			logger.error("Uncaught {} Detected!", marshalString(ex->InnerException->GetType()->ToString()));
			logger.error(marshalString(ex->InnerException->ToString()));
		}
		catch (System::Exception^ ex)
		{
			logger.error("Uncaught {} Detected!", marshalString(ex->GetType()->ToString()));
			logger.error(marshalString(ex->ToString()));
		}
		catch (const std::exception& ex)
		{
			logger.error("Uncaught std::exception Detected!");
			logger.error(ex.what());
		}
		catch (...)
		{
			logger.error("Uncaught exception Detected!");
		}
	}
	logger.info << count << " plugin(s) loaded" << logger.endl;
}

#pragma unmanaged
#include "Global.hpp"
#include <Utils/Hash.h>

#pragma unmanaged
void CheekPluginEntry(std::vector<std::filesystem::path>& assemblyPaths, Logger& logger);

#pragma unmanaged
void LoadMain()
{
	Logger logger(LLNET_LOADER_NAME);

	Init(logger);

	logger.info("Loading plugins...");
	std::filesystem::directory_iterator files(LLNET_PLUGINS_LOAD_DIR);
	std::vector<std::filesystem::path> assemblies;
	for (auto& file : files)
	{
		auto& filePath = file.path();
		if (filePath.extension() == ".dll")
		{
			if (filePath.filename() == LLNET_LOADER_NAME_WITH_EXTENSION)
				continue;
			assemblies.emplace_back(filePath);
		}
	}

	CheekPluginEntry(assemblies, logger);

	LoadPlugins(assemblies, logger);
}

#pragma unmanaged
void CheekPluginEntry(std::vector<std::filesystem::path>& assemblyPaths, Logger& logger)
{
	PEHeader info;

	for (auto iter = assemblyPaths.begin(); iter != assemblyPaths.end();)
	{
		info.read(*iter);

		if (info.isDotNETAssembly())
		{
			auto dllFile = fopen(iter->string().c_str(), "r");
			if (dllFile != nullptr)
			{

				long pos = 0x0000049c;
				bool signal = false;
				char val = 0;
				char buffer[9]{ 0 };

				fseek(dllFile, 0L, SEEK_END);
				auto end = ftell(dllFile);

				while (pos < end)
				{
					fseek(dllFile, pos++, SEEK_SET);
					val = fgetc(dllFile);

					if (val != 0x4f)
						continue;
					else
					{
						fread(buffer, sizeof(char), 9, dllFile);

						if (!bool(buffer[0] ^ 0x6e |
							buffer[1] ^ 0x50 |
							buffer[2] ^ 0x6f |
							buffer[3] ^ 0x73 |
							buffer[4] ^ 0x74 |
							buffer[5] ^ 0x49 |
							buffer[6] ^ 0x6e |
							buffer[7] ^ 0x69 |
							buffer[8] ^ 0x74))
						{
							signal = true;
							break;
						}
					}
				}

				if (signal)
					++iter;
				else
				{
					iter = assemblyPaths.erase(iter);
				}
				fclose(dllFile);
			}
		}
		else
		{
			iter = assemblyPaths.erase(iter);
		}
	}
}