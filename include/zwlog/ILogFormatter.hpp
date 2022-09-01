#pragma once

#include <string>
#include <memory>
#include <utility>
#include <type_traits>

namespace zwlog
{
	class LogContext;

	class ILogFormatter
	{
	public:
		virtual ~ILogFormatter() = 0;
		virtual std::string Format(const LogContext& context) = 0;

	protected:
		template <typename T, typename... TArgs>
			requires std::is_base_of_v<ILogFormatter, T>&& std::is_constructible_v<T, TArgs&&...>
		static std::shared_ptr<T> CreateInternal(TArgs&&... args)
		{
			return std::make_shared<T>(std::forward<TArgs>(args)...);
		}
	};

	inline ILogFormatter::~ILogFormatter() = default;
}