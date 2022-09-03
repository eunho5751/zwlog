#pragma once

#include <cstdint>
#include <source_location>
#include <string>
#include <sstream>
#include <utility>

namespace zwlog
{
	class LogContext
	{
	public:
		explicit LogContext(int severity_id, const std::source_location& location = std::source_location::current());

		template <typename T>
		LogContext& operator<<(T&& content)
		{
			stream_ << std::forward<T>(content);
			return *this;
		}

		std::string GetLog() const&;
		std::string GetLog()&&;
		int GetSeverityId() const noexcept;
		uint_least32_t GetLine() const noexcept;
		uint_least32_t GetColumn() const noexcept;
		const char* GetFileName() const noexcept;
		const char* GetFunctionName() const noexcept;

	private:
		int severity_id_;
		std::source_location location_;
		std::ostringstream stream_;
	};
}