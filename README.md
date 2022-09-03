# zwlog
zwlog is a simple logging library written with modern C++ features.

<br/>

## Overview
The image below shows how logs are processed in this library.
<img width="100%" alt="image" src="https://user-images.githubusercontent.com/29402080/188267405-c7dd7bc9-d51b-43c8-aa22-8be0d059dd4e.png">

When you do loggings by `LOG`, A `LogContext` class instance is created. it contains some useful information such as your message, the severity tag, and even the file name and function name where the log is emitted. `Logger` then takes the `LogContext` and sends it to `LogTarget*`s added to `Logger`. `LogTargt*`s make a new formatted log by using its formatter. Through the formatter, the log now would contain not only your message but also some information in the `LogContext`. Finally, the log is written to the destinations such as the console buffer, and physical file.

<br/>

## Requirements
- C++20 or higher

<br/>

## How To Use
### Severity Configuration
1. **Include <zwlog/Logger.hpp>**

```c++
#include <zwlog/Logger.hpp>
```

<br/>

2. **Define your own enum to use as severity levels**

```c++
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

3. **Set a tag of each severity level**

```c++
zwlog::Get().SetSeverity(Severity::Info, "Info");
zwlog::Get().SetSeverity(Severity::Warning, "Warning");
zwlog::Get().SetSeverity(Severity::Error, "Error");
```
A Tag is used to represent each severity level as a string.

<br/>

### LogTarget Configuration
1. **Include `<zwlog/LogTarget*.hpp>` you want to use** <br/>
( Currently 2 default log targets are supported ) 

```c++
#include <zwlog/LogTargetConsole.hpp> // or LogTargetFile.hpp
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
zwlog::Get().AddTarget(console_target);
```
`Logger` now can recognize where to output logs without having you designate the target.

<br/>

### Logging
1. **Include <zwlog/Logger.hpp>**

```c++
#include <zwlog/Logger.hpp>
```

<br/>

2. **Use `LOG` to output logs**

```c++
std::string name = "Eunho Choi";
LOG(Severity::Info) << "My name is " << name << '\n';
```
