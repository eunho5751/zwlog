
#include "zwlog/MessageFormatter.hpp"
#include "zwlog/Logger.hpp"

#include <format>

namespace zwlog
{
	std::string MessageFormatter::Format(const LogContext& context)
	{
		std::string fmt = std::format(kFormatString, Get().GetSeverityTag(context.GetSeverityId()), context.GetLog());
		return fmt;
	}

	std::shared_ptr<MessageFormatter> MessageFormatter::Create()
	{
		return CreateInternal<MessageFormatter>();
	}
}
