#pragma once

#include "LogTargetBase.hpp"

#include <memory>

namespace zwlog
{
	class LogTargetConsole : public LogTargetBase
	{
	public:
		enum class ConsoleType
		{
			Out,
			Err,
			Log
		};

	public:
		LogTargetConsole(ConsoleType type);

		void Flush() override;
		bool ShouldFlush() const noexcept override;
		ConsoleType GetType() const noexcept;

		static std::shared_ptr<LogTargetConsole> Create(ConsoleType type);

	protected:
		void Write(std::string_view str) override;

	private:
		ConsoleType type_;
		std::ostream& stream_;
	};
}