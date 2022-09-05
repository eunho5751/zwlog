#pragma once

#include "zwlog/LogContext.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#define LOG(group_id, severity_id) zwlog::Get() += zwlog::LogContext(group_id, severity_id)

namespace zwlog
{
	class Logger;
	class LogTargetBase;

	Logger& Get();

	class Logger
	{
		using targets_type = std::vector<std::shared_ptr<LogTargetBase>>;

		friend Logger& Get();

	public:
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

		Logger& operator+=(LogContext& context);

		void AddTarget(int group_id, std::shared_ptr<LogTargetBase> target);
		void RemoveTarget(int group_id, const std::shared_ptr<LogTargetBase>& target);

		void SetSeverity(int severity_id, std::string tag);
		const std::string& GetSeverityTag(int severity_id) const noexcept;
		bool HasSeverity(int severity_id) const noexcept;

	private:
		Logger();
		~Logger() = default;

	private:
		std::unordered_map<int, std::string> severity_tag_map_;
		std::unordered_map<int, targets_type> group_targets_map_;
	};
}