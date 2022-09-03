# zwlog
zwlog is a simple logging library written with modern C++ features.

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

<br/>

### LogTarget Configuration

<br/>

### Logging
