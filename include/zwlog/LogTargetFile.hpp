#pragma once

#include "zwlog/LogTargetBase.hpp"

#include <string>
#include <fstream>
#include <memory>

namespace zwlog
{
	class LogTargetFile : public LogTargetBase
	{
	public:
		enum class OpenMode
		{
			// Create a new file with a suffixed name and open it.
			Create,

			// Open an existing file and clear its content.
			// If the file does not exist, create a new file and open it.
			Clear,

			// Open an existing file and append logs at the end of file stream.
			// If the file does not exist, create a new file and open it.
			Append
		};

	public:
		explicit LogTargetFile(std::string file_name, OpenMode open_mode = OpenMode::Create);
		~LogTargetFile() override;

		LogTargetFile(const LogTargetFile&) = delete;
		LogTargetFile(LogTargetFile&&) = default;
		LogTargetFile& operator=(const LogTargetFile&) = delete;
		LogTargetFile& operator=(LogTargetFile&&) = default;

		void Flush() override;
		bool ShouldFlush() const override;

		const std::string& GetFileName() const noexcept;
		OpenMode GetOpenMode() const noexcept;

		static std::shared_ptr<LogTargetFile> Create(std::string file_name, OpenMode open_mode = OpenMode::Create);

	protected:
		void Write(std::string_view str) override;

	private:
		std::string file_name_;
		OpenMode open_mode_;
		std::ofstream file_stream_;
	};
}