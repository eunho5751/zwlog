
#include "zwlog/LogTargetConsole.hpp"

#include <iostream>

namespace zwlog
{
	LogTargetConsole::LogTargetConsole(ConsoleType type) :
		type_(type),
		stream_(type == ConsoleType::Out ? std::cout : (type == ConsoleType::Err ? std::cerr : std::clog))
	{

	}

	void LogTargetConsole::Flush()
	{
		stream_ << std::flush;
	}

	bool LogTargetConsole::ShouldFlush() const noexcept
	{
		// we don't have to flush cerr because it does not use buffer
		return type_ != ConsoleType::Err ? true : false;
	}

	LogTargetConsole::ConsoleType LogTargetConsole::GetType() const noexcept
	{
		return type_;
	}

	void LogTargetConsole::Write(std::string_view str)
	{
		stream_ << str;
	}
	
	std::shared_ptr<LogTargetConsole> LogTargetConsole::Create(ConsoleType type)
	{
		return CreateInternal<LogTargetConsole>(type);
	}
}
