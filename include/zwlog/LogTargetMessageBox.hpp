#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN

#include "zwlog/LogTargetBase.hpp"

#include <memory>

namespace zwlog
{
	class LogTargetMessageBox : public LogTargetBase
	{
	public:
		void Flush() override;
		bool ShouldFlush() const override;

		static std::shared_ptr<LogTargetMessageBox> Create();

	protected:
		void Write(const LogContext& context, std::string_view formatted_log) override;
	};
}

#endif