
#include "zwlog/LogTargetFile.hpp"

#include <chrono>
#include <format>
#include <filesystem>
#include <utility>

namespace zwlog
{
	LogTargetFile::LogTargetFile(std::string file_name, OpenMode open_mode) : open_mode_(open_mode)
	{
		// Create directories if not exists
		if (auto sep_idx = file_name.find_last_of('/'); sep_idx != std::string::npos && sep_idx != 0)
		{
			std::string directories = file_name.substr(0, sep_idx);
			std::filesystem::create_directories(directories);
		}

		std::ios_base::openmode mode = std::ios_base::out;
		switch (open_mode_)
		{

		case OpenMode::Create:
		{
			using namespace std::chrono;

			auto local_time = zoned_time(current_zone(), system_clock::now()).get_local_time();
			std::string time_string = std::format("{0:%Y%m%d%H%M}", local_time);
			
			if (auto ext_idx = file_name.find_last_of('.'); ext_idx != std::string::npos)
			{
				std::string name = file_name.substr(0, ext_idx);
				std::string ext = file_name.substr(std::min(file_name.length() - 1, ext_idx + 1));
				file_name_ = std::format("{}_{}.{}", name, time_string, ext);
			}
			else
			{
				file_name_ = std::format("{}_{}", file_name, time_string);
			}
		}
		break;

		case OpenMode::Clear:
		{
			file_name_ = std::move(file_name);
			mode |= std::ios_base::trunc;
		}
		break;

		case OpenMode::Append:
		{
			file_name_ = std::move(file_name);
			mode |= std::ios_base::app;
		}
		break;

		}

		file_stream_.open(file_name_, mode);
	}

	LogTargetFile::~LogTargetFile()
	{
		if (file_stream_.is_open())
		{
			file_stream_.close();
		}
	}

	void LogTargetFile::Flush()
	{
		file_stream_ << std::flush;
	}

	bool LogTargetFile::ShouldFlush() const
	{
		return true;
	}

	void LogTargetFile::Write(const LogContext& context, std::string_view formatted_log)
	{
		file_stream_ << formatted_log;
	}

	const std::string& LogTargetFile::GetFileName() const noexcept
	{
		return file_name_;
	}

	LogTargetFile::OpenMode LogTargetFile::GetOpenMode() const noexcept
	{
		return open_mode_;
	}

	std::shared_ptr<LogTargetFile> LogTargetFile::Create(std::string file_name, OpenMode open_mode)
	{
		return CreateInternal<LogTargetFile>(std::move(file_name), open_mode);
	}
}
