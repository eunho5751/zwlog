
#include "zwlog/DefaultFormatter.hpp"
#include "zwlog/Logger.hpp"

namespace zwlog
{
	std::string DefaultFormatter::Format(const LogContext& context)
	{
		return FormatHelper(kFormatString, context);
	}

	std::shared_ptr<DefaultFormatter> DefaultFormatter::Create()
	{
		return CreateInternal<DefaultFormatter>();
	}
}
