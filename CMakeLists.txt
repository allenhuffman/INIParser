cmake_minimum_required(VERSION 3.10.0)
project(INIParserTest VERSION 0.1.0 LANGUAGES C)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Add files to a GLOB variable
file(GLOB SOURCES "*.c" "*.h")

add_executable(INIParserTest ${SOURCES})
