
#ifdef _WIN32

#include "zwlog/LogTargetMessageBox.hpp"
#include "zwlog/LogContext.hpp"
#include "zwlog/Logger.hpp"

#include <windows.h>

namespace zwlog
{
	void LogTargetMessageBox::Write(const LogContext& context, std::string_view formatted_log)
	{
		LPCSTR caption = Get().GetSeverityTag(context.GetSeverityId()).c_str();
		LPCSTR text = formatted_log.data();
		MessageBox(NULL, text, caption, MB_OK);
	}

	void LogTargetMessageBox::Flush()
	{
	}

	bool LogTargetMessageBox::ShouldFlush() const
	{
		return false;
	}

	std::shared_ptr<LogTargetMessageBox> LogTargetMessageBox::Create()
	{
		return CreateInternal<LogTargetMessageBox>();
	}
}

#endif