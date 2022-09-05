#pragma once

#include "zwlog/ILogFormatter.hpp"
#include "zwlog/LogContext.hpp"

#include <string>
#include <memory>

namespace zwlog
{
	class MessageFormatter : public ILogFormatter
	{
		inline static constexpr const char* kFormatString = "[{}] {}\n";

	public:
		std::string Format(const LogContext& context) override;

		static std::shared_ptr<MessageFormatter> Create();
	};
}