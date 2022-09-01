
#include "zwlog/LogContext.hpp"

namespace zwlog
{
	LogContext::LogContext(std::pair<int, std::string> severity, const std::source_location& location) : severity_(std::move(severity)), location_(location)
	{

	}

	std::string LogContext::GetLog() const&
	{
		return stream_.str();
	}

	std::string LogContext::GetLog()&&
	{
		return std::move(stream_).str();
	}

	const std::pair<int, std::string>& LogContext::GetSeverity() const noexcept
	{
		return severity_;
	}

	uint_least32_t LogContext::GetLine() const noexcept
	{
		return location_.line();
	}

	uint_least32_t LogContext::GetColumn() const noexcept
	{
		return location_.column();
	}

	const char* LogContext::GetFileName() const noexcept
	{
		return location_.file_name();
	}

	const char* LogContext::GetFunctionName() const noexcept
	{
		return location_.function_name();
	}
}