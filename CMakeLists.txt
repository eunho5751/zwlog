cmake_minimum_required(VERSION 3.1)
project(zwlog)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR src)
set(HEADER_DIR include/zwlog)

set(SOURCES "")

set(HEADERS "")

add_library(zwlog ${SOURCES} ${HEADERS})
target_include_directories(zwlog PUBLIC include)