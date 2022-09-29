# zwlog
zwlog is a simple logging library written with modern C++ features.

<br/>

## Overview
The image below shows how logs are processed in this library.

<img width="100%" alt="image" src="https://user-images.githubusercontent.com/29402080/192958333-37ce593a-1e4a-40e0-a638-496de72c6498.png">

<br/>

## Requirements
- C++20 or higher
- CMake

<br/>

## Usage
```c++
#include <zwlog/Logger.hpp>
#include <zwlog/LogTargetFile.hpp>
#include <zwlog/LogTargetMessageBox.hpp>
#include <zwlog/DefaultFormatter.hpp>

// Here, namespace is used to make a scope for enumerators instead of enum class
// because you need to cast it to integer explicitly for each use if you use enum class
namespace LogGroup
{
  enum
  {
    Default = 0,
    Fatal
  }
}

// ditto
namespace LogSeverity
{
  enum
  {
    Info = 0,
    Warning,
    Error
  }
}

int main()
{
  // Set tags for severities
  // Tags are used by log formatters
  zwlog::SetSeverity(LogSeverity::Info, "Info");
  zwlog::SetSeverity(LogSeverity::Warning, "Warning");
  zwlog::SetSeverity(LogSeverity::Error, "Error");

  // Create log targets
  // Your logs are written to these targets
  auto file_target = zwlog::LogTargetFile::Create("logs/log.txt");
  auto msgbox_target = zwlog::LogTargetMessageBox::Create();
  
  // Create log formatters 
  // Log formatters are used to add useful information to your logs
  // EX) [Error] Error Occurred!!
  //     -- 15:36:22 PM | File: main.cpp | Line: 32 | Func: main --
  auto default_formatter = zwlog::DefaultFormatter::Create();
  
  // Assign log formatters to log targets
  // (Log targets basically use DefaultFormatter, so you don't have to do this in practice)
  file_target.SetFormatter(default_formatter);
  msgbox_target.SetFormatter(default_formatter);
  
  // Add log targets to the specified group
  zwlog::AddTarget(LogGroup::Default, file_target);
  zwlog::AddTarget(LogGroup::Fatal, file_target);
  zwlog::AddTarget(LogGroup::Fatal, msgbox_target);
  
  // Logs are written to 'log.txt' file
  LOG(LogGroup::Default, LogSeverity::Info) << "My Message!" << ' ' << "Hi!";
  /*
    [Info] My Message! Hi!
    -- 17:22:10 PM | File: main.cpp | Line: 63 | Func: main --
  */
  
  // Logs are written to 'log.txt' file and displayed in the message box
  LOG(LogGroup::Fatal, LogSeverity::Error) << "Fatal Error Occured!";
  /*
    [Error] Fatal Error Occurred!!
    -- 17:22:13 PM | File: main.cpp | Line: 64 | Func: main --
  */
}

```

