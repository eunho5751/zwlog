#pragma once

#include "zwlog/LogFormatterBase.hpp"

#include <memory>

namespace zwlog
{
	class DefaultFormatter : public LogFormatterBase
	{
		inline static constexpr const char* kFormatString = 
			"[{SEVERITY}] {MSG}\n"
			"-- {TIME} |  File: {FILE} | Line: {LINE} | Func: {FUNC} --";

	public:
		std::string Format(const LogContext& context) override;

		static std::shared_ptr<DefaultFormatter> Create();
	};
}