
#include "zwlog/DefaultFormatter.hpp"

#include <format>

namespace zwlog
{
	std::string DefaultFormatter::Format(const LogContext& context)
	{
		std::string fmt = std::format(kFormatString,
			context.GetSeverity().second, context.GetLog(), context.GetFileName(), context.GetLine(), context.GetFunctionName());
		return fmt;
	}

	std::shared_ptr<DefaultFormatter> DefaultFormatter::Create()
	{
		return CreateInternal<DefaultFormatter>();
	}
}
