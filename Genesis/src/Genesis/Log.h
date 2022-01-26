#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

#include <memory>

namespace Genesis {

	class GENESIS_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define GS_CORE_TRACE(...)   ::Genesis::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GS_CORE_INFO(...)    ::Genesis::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GS_CORE_WARN(...)    ::Genesis::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GS_CORE_ERROR(...)   ::Genesis::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GS_CORE_FATAL(...)   ::Genesis::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define GS_TRACE(...)        ::Genesis::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GS_INFO(...)         ::Genesis::Log::GetClientLogger()->info(__VA_ARGS__)
#define GS_WARN(...)         ::Genesis::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GS_ERROR(...)        ::Genesis::Log::GetClientLogger()->error(__VA_ARGS__)
#define GS_FATAL(...)        ::Genesis::Log::GetClientLogger()->fatal(__VA_ARGS__)
