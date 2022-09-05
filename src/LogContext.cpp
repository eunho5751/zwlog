
#include "zwlog/LogContext.hpp"

namespace zwlog
{
	LogContext::LogContext(int group_id, int severity_id, const std::source_location& location) : group_id_(group_id), severity_id_(severity_id), location_(location)
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

	int LogContext::GetGroupId() const noexcept
	{
		return group_id_;
	}

	int LogContext::GetSeverityId() const noexcept
	{
		return severity_id_;
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