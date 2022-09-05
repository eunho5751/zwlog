
#include "zwlog/Logger.hpp"
#include "zwlog/LogContext.hpp"
#include "zwlog/LogTargetBase.hpp"

#include <utility>

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

	}

	Logger& Logger::operator+=(LogContext& context)
	{
		if (auto it = group_targets_map_.find(context.GetGroupId()); it != group_targets_map_.end())
		{
			for (const auto& target : it->second)
			{
				target->Write(context);
				if (target->ShouldFlush())
				{
					target->Flush();
				}
			}
		}

		return *this;
	}

	void Logger::AddTarget(int group_id, std::shared_ptr<LogTargetBase> target)
	{
		if (auto it = group_targets_map_.find(group_id); it != group_targets_map_.end())
		{
			it->second.push_back(std::move(target));
		}
		else
		{
			group_targets_map_.try_emplace(group_id, targets_type { std::move(target)});
		}
	}

	void Logger::RemoveTarget(int group_id, const std::shared_ptr<LogTargetBase>& target)
	{
		if (auto it = group_targets_map_.find(group_id); it != group_targets_map_.end())
		{
			std::erase_if(it->second, [&target](const std::shared_ptr<LogTargetBase>& elem) { return target == elem; });
		}
	}

	void Logger::SetSeverity(int severity_id, std::string tag)
	{
		severity_tag_map_[severity_id] = std::move(tag);
	}

	const std::string& Logger::GetSeverityTag(int severity_id) const noexcept
	{
		if (const auto& it = severity_tag_map_.find(severity_id); it != severity_tag_map_.end())
		{
			return it->second;
		}

		// severity tag is not found
		static std::string undef_severity = "Undefined Severity";
		return undef_severity;
	}

	bool Logger::HasSeverity(int severity_id) const noexcept
	{
		return severity_tag_map_.contains(severity_id);
	}
}
