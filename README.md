# zwlog
zwlog is a simple logging library written with modern C++ features.

<br/>

## Overview
The image below shows how logs are processed in this library.
<img width="100%" alt="image" src="https://user-images.githubusercontent.com/29402080/188460818-d71b7f93-54d9-4ea6-8cd9-18b1d5b4525f.png">

When you do loggings by `LOG`, A `LogContext` class instance is created. it contains some useful information such as your log message, a severity level, and even a file name and function name where the log is emitted. `Logger` then takes the `LogContext` and sends it to `LogTarget*`s of the group you inputted in `LOG`. Each of the `LogTargt*`s makes a new formatted log by using its formatter. Through the formatter, the log now would contain not only your log message but also some information in the `LogContext`. Finally, the log is written to the destinations such as a console buffer, and physical file.

<br/>

## Requirements
- C++20 or higher

<br/>

## Constructs
- **Severity** <br/>
Severity is integers used to indicate how serious your log is. You can define `enum` or `const int` to name each severity integer to avoid confusion. You also must set a tag for each severity level. The tag is used to format your log like `"[Error] Fatal error occured!"`, but how it will be used is not limited to the previous case.  

- **LogTarget** <br/>
LogTarget defines where and how logs are outputted. For example, currently provided `LogTargetConsole` and `LogTargetFile` output logs to their console buffer and file, respectively. Your application can create multiple log targets and output logs to them at the same time. This is useful when you want to display logs in UI and then save them to a file to check them back again later.

- **LogFormatter** <br/>
- **Group** <br/>
- **LogContext** <br/>
- **Logger**

<br/>

## How To Use
### Severity Configuration
1. **Define your own compile-time constants to use as severity levels**

This step is required to name each integer severity level. <br/>

```c++
// LogConstants.hpp
enum Severity
{
  Info      = 0,
  Warning,
  Error
};
```
You don't necessarily have to define an `enum`, but whatever method you use, each severity level must be able to be cast to an integer. <br/>
For that reason, it's not recommended to use `enum class` because it requires you to explicitly cast it to an integer.

<br/>

2. **Set tags for each severity level**

```c++
#include <zwlog/Logger.hpp>
#include "LogConstants.hpp"

...

zwlog::Get().SetSeverity(Severity::Info, "Info");
zwlog::Get().SetSeverity(Severity::Warning, "Warning");
zwlog::Get().SetSeverity(Severity::Error, "Error");
```

<br/>

### Group Configuration
This step is required to name each integer group id, as is the case with `enum` in Severity Configuration. <br/>

```c++
// LogConstants.hpp
enum Group
{
  Editor  = 0,
  Engine
};
```

<br/>

### LogTarget Configuration
1. **Include `zwlog/LogTarget*.hpp` and the header file where the constants defined above exist** <br/>
 

```c++
#include <zwlog/LogTargetConsole.hpp>
#include "LogConstants.hpp"
```

<br/>

2. **Create a log target instance**

```c++
auto console_target = zwlog::LogTargetConsole::Create(zwlog::LogTargetConsole::ConsoleType::Out);
```

<br/>

3. **Add the target to `Logger`**

```c++
auto console_target = ···;
zwlog::Get().AddTarget(Group::Editor, console_target);
```

<br/>

### Logging

```c++
#include <zwlog/Logger.hpp>
#include "LogConstants.hpp"

...

std::string name = "Eunho Choi";
LOG(Group::Editor, Severity::Info) << "My name is " << name << '\n';
```

It would be tiresome to include multiple header files one by one when logging. <br/>
So, I recommend that you create a new header file that includes zwlog/Logger.hpp and severity/group enums. <br/>
