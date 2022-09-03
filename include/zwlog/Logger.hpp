#pragma once

#include "zwlog/LogContext.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#define LOG(severity_id) zwlog::Get() += zwlog::LogContext(severity_id)

namespace zwlog
{
	class Logger;
	class LogTargetBase;

	Logger& Get();

	class Logger
	{
		friend Logger& Get();

	public:
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

		Logger& operator+=(LogContext& context);

		void AddTarget(std::shared_ptr<LogTargetBase> target);
		void RemoveTarget(const std::shared_ptr<LogTargetBase>& target);

		void SetSeverity(int severity_id, std::string tag);
		const std::string& GetSeverityTag(int severity_id) const noexcept;
		bool HasSeverity(int severity_id) const noexcept;

	private:
		Logger();
		~Logger() = default;

	private:
		std::unordered_map<int, std::string> severity_tag_map_;
		std::vector<std::shared_ptr<LogTargetBase>> targets_;
	};
}