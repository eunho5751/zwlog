
#include "zwlog/Logger.hpp"
#include "zwlog/LogContext.hpp"
#include "zwlog/LogTargetBase.hpp"

namespace zwlog
{
	/* static functions */

	Logger& Get()
	{
		static Logger logger;
		return logger;
	}

	/* member functions */

	Logger::Logger()
	{
		SetSeverity(-1, "Undefined Severity");
	}

	Logger& Logger::operator+=(LogContext& context)
	{
		for (const auto& target : targets_)
		{
			target->Write(context);
			if (target->ShouldFlush())
			{
				target->Flush();
			}
		}

		return *this;
	}

	void Logger::AddTarget(std::shared_ptr<LogTargetBase> target)
	{
		targets_.push_back(std::move(target));
	}

	void Logger::RemoveTarget(const std::shared_ptr<LogTargetBase>& target)
	{
		std::erase_if(targets_, [&target](const std::shared_ptr<LogTargetBase>& elem) { return target == elem; });
	}

	void Logger::SetSeverity(int severity_id, std::string tag)
	{
		if (severity_id == -1)
		{
			// -1 is reserved to indicate that the severity is not set 
			return;
		}

		severity_tag_map_[severity_id] = std::move(tag);
	}

	const std::string& Logger::GetSeverityTag(int severity_id) const noexcept
	{
		if (const auto& it = severity_tag_map_.find(severity_id); it != severity_tag_map_.end())
		{
			return it->second;
		}

		// severity tag is not found
		return severity_tag_map_.at(-1);
	}

	bool Logger::HasSeverity(int severity_id) const noexcept
	{
		return severity_tag_map_.contains(severity_id);
	}
}
