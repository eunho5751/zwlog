
#include "zwlog/LogTargetBase.hpp"
#include "zwlog/DefaultFormatter.hpp"

#include <utility>

namespace zwlog
{
	LogTargetBase::LogTargetBase()
	{
		SetFormatter(nullptr);
	}

	void LogTargetBase::SetFormatter(std::shared_ptr<LogFormatterBase> formatter)
	{
		formatter_ = std::move(formatter);
		if (formatter_ == nullptr)
		{
			formatter_ = std::make_shared<DefaultFormatter>();
		}
	}

	void LogTargetBase::Write(const LogContext& context)
	{
		std::string fmt = formatter_->Format(context);
		fmt += "\n\n";

		Write(context, fmt);
	}
}
