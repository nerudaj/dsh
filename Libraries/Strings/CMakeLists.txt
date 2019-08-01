cmake_minimum_required (VERSION 3.4)
project (strings)

# Export all symbols in dynamic library
set (CMAKE_INSTALL_PREFIX /tools)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set (CMAKE_GENERATOR_PLATFORM x64)

if (NOT CMAKE_DEBUG_POSTFIX)
	set(CMAKE_DEBUG_POSTFIX "-d")
endif()

# Add library
add_library(${PROJECT_NAME} Strings.cpp)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES Strings.hpp DESTINATION include)

# Add testrunner
include_directories(/tools/include)
add_executable(testrunner tests/Main.cpp)
target_link_libraries(testrunner ${PROJECT_NAME})