
#include "zwlog/SourceLocationFormatter.hpp"
#include "zwlog/Logger.hpp"

#include <format>

namespace zwlog
{
	std::string SourceLocationFormatter::Format(const LogContext& context)
	{
		std::string fmt = std::format(kFormatString,
			Get().GetSeverityTag(context.GetSeverityId()), context.GetLog(), context.GetFileName(), context.GetLine(), context.GetFunctionName());
		return fmt;
	}

	std::shared_ptr<SourceLocationFormatter> SourceLocationFormatter::Create()
	{
		return CreateInternal<SourceLocationFormatter>();
	}
}
