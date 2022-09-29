
#include "zwlog/LogFormatterBase.hpp"
#include "zwlog/Logger.hpp"

#include <chrono>
#include <format>
#include <optional>

namespace zwlog
{
	std::string LogFormatterBase::FormatHelper(std::string_view fmt, const LogContext& context)
	{
		std::string log{ fmt };

		auto get_value = [&context](std::string_view tag)->std::optional<std::string>
		{
			if (tag == "{DATE}")
			{
				using namespace  std::chrono;
				auto time = zoned_time{ current_zone(), system_clock::now()}.get_local_time();
				return std::format("{0:%F}", time);
			}
			if (tag == "{TIME}")
			{
				using namespace  std::chrono;
				auto time = zoned_time{ current_zone(), system_clock::now() }.get_local_time();
				return std::format("{0:%X} {0:%p}", time);
			}
			if (tag == "{SEVERITY}") { return GetSeverityTag(context.GetSeverityId()); }
			if (tag == "{FILE}") { return context.GetFileName(); }
			if (tag == "{LINE}") { return std::to_string(context.GetLine()); }
			if (tag == "{FUNC}") { return context.GetFunctionName(); }
			if (tag == "{COLUMN}") { return std::to_string(context.GetColumn()); }
			if (tag == "{MSG}") { return context.GetLog(); }
			return std::nullopt;
		};

		std::string::size_type pos{};
		while ((pos = log.find('{', pos)) != log.npos)
		{
			auto pos_end = log.find('}', pos + 1);
			if (pos_end != log.npos)
			{
				auto count = pos_end - pos + 1;

				std::string tag = log.substr(pos, count);
				auto value = get_value(tag);
				if (value.has_value())
				{
					log = log.replace(pos, count, *value);
					pos += value->length();
					continue;
				}
			}

			pos++;
		}

		return log;
	}
}
