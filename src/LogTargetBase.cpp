
#include "zwlog/LogTargetBase.hpp"
#include "zwlog/MessageFormatter.hpp"

#include <utility>

namespace zwlog
{
	LogTargetBase::LogTargetBase()
	{
		SetFormatter(nullptr);
	}

	void LogTargetBase::SetFormatter(std::shared_ptr<ILogFormatter> formatter)
	{
		formatter_ = std::move(formatter);
		if (formatter_ == nullptr)
		{
			formatter_ = std::make_shared<MessageFormatter>();
		}
	}

	void LogTargetBase::Write(const LogContext& context)
	{
		std::string fmt = formatter_->Format(context);
		Write(fmt);
	}
}
