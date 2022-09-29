#pragma once

#include "zwlog/LogContext.hpp"

#include <string>
#include <string_view>
#include <memory>
#include <utility>
#include <type_traits>

namespace zwlog
{
	class LogContext;

	class LogFormatterBase
	{
	public:
		virtual ~LogFormatterBase() = default;
		virtual std::string Format(const LogContext& context) = 0;

	protected:
		virtual std::string FormatHelper(std::string_view fmt, const LogContext& context);
		
		template <typename T, typename... TArgs>
			requires std::is_base_of_v<LogFormatterBase, T>&& std::is_constructible_v<T, TArgs&&...>
		static std::shared_ptr<T> CreateInternal(TArgs&&... args)
		{
			return std::make_shared<T>(std::forward<TArgs>(args)...);
		}
	};
}
