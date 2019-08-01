cmake_minimum_required (VERSION 3.4)
project (config)

set (CMAKE_INSTALL_PREFIX /tools)
include_directories(/tools/include)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

if (NOT CMAKE_DEBUG_POSTFIX)
	set(CMAKE_DEBUG_POSTFIX "-d")
endif()

# Add library
add_library(${PROJECT_NAME} Args.cpp Csv.cpp Ini.cpp Item.cpp)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install
install(TARGETS config DESTINATION lib)
install(FILES Config.hpp Args.hpp Csv.hpp Ini.hpp Item.hpp DESTINATION include)

add_executable(testrunner tests/Main.cpp)
find_library(LIB_LOG NAMES logger)
find_library(LIB_STR NAMES strings)
target_link_libraries(testrunner ${PROJECT_NAME} ${LIB_LOG} ${LIB_STR})
