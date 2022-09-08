cmake_minimum_required(VERSION 3.1)
project(zwlog)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR src)
set(HEADER_DIR include/zwlog)

set(SOURCES 
	${SOURCE_DIR}/Logger.cpp
	${SOURCE_DIR}/LogContext.cpp
	${SOURCE_DIR}/LogTargetBase.cpp

	${SOURCE_DIR}/MessageFormatter.cpp
	${SOURCE_DIR}/SourceLocationFormatter.cpp

	${SOURCE_DIR}/LogTargetConsole.cpp
	${SOURCE_DIR}/LogTargetFile.cpp
	${SOURCE_DIR}/LogTargetMessageBox.cpp)

set(HEADERS 
	${HEADER_DIR}/Logger.hpp
	${HEADER_DIR}/LogContext.hpp
	${HEADER_DIR}/LogTargetBase.hpp
	${HEADER_DIR}/ILogFormatter.hpp

	${HEADER_DIR}/MessageFormatter.hpp
	${HEADER_DIR}/SourceLocationFormatter.hpp

	${HEADER_DIR}/LogTargetConsole.hpp
	${HEADER_DIR}/LogTargetFile.hpp
	${HEADER_DIR}/LogTargetMessageBox.hpp)

add_library(zwlog ${SOURCES} ${HEADERS})
target_include_directories(zwlog PUBLIC include)