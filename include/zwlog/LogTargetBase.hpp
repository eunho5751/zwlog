#pragma once

#include "zwlog/LogFormatterBase.hpp"

#include <string_view>
#include <memory>
#include <type_traits>

namespace zwlog
{
	class LogTargetBase
	{
	public:
		LogTargetBase();
		virtual ~LogTargetBase() = default;

		LogTargetBase(const LogTargetBase&) = default;
		LogTargetBase(LogTargetBase&&) = default;
		LogTargetBase& operator=(const LogTargetBase&) = default;
		LogTargetBase& operator=(LogTargetBase&&) = default;

		void SetFormatter(std::shared_ptr<LogFormatterBase> formatter);

		template <typename T> requires std::is_base_of_v<LogFormatterBase, T>
		std::shared_ptr<T> GetFormatter() const
		{
			return std::dynamic_pointer_cast<T>(formatter_);
		}

		void Write(const LogContext& context);
		virtual void Flush() = 0;
		virtual bool ShouldFlush() const = 0;

	protected:
		virtual void Write(const LogContext& context, std::string_view formatted_log) = 0;

		template <typename T, typename... TArgs>
			requires std::is_base_of_v<LogTargetBase, T> && std::is_constructible_v<T, TArgs&&...>
		static std::shared_ptr<T> CreateInternal(TArgs&&... args)
		{
			return std::make_shared<T>(std::forward<TArgs>(args)...);
		}

	private:
		std::shared_ptr<LogFormatterBase> formatter_;
	};
}