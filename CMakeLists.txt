cmake_minimum_required(VERSION 3.10.0)
project(INIParserTest VERSION 0.1.0 LANGUAGES C)

add_executable(INIParserTest ErrnoToCVIStatus.c INIParser.c INIParserGettingValuesFromTags.c INIParserInformational.c INIParserManagement.c INIParserPuttingTagValuePairs.c INIParserRemovingSectionsAndItems.c INIRecords.c Utilities.c main.c)

# Add warning flags for GCC and Clang
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()
