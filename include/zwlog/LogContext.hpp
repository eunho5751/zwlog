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
		explicit LogContext(std::pair<int, std::string> severity, const std::source_location& location = std::source_location::current());

		template <typename T>
		LogContext& operator<<(T&& content)
		{
			stream_ << std::forward<T>(content);
			return *this;
		}

		std::string GetLog() const&;
		std::string GetLog()&&;
		const std::pair<int, std::string>& GetSeverity() const noexcept;
		uint_least32_t GetLine() const noexcept;
		uint_least32_t GetColumn() const noexcept;
		const char* GetFileName() const noexcept;
		const char* GetFunctionName() const noexcept;

	private:
		std::pair<int, std::string> severity_;
		std::source_location location_;
		std::ostringstream stream_;
	};
}