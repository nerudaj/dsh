cmake_minimum_required (VERSION 3.4)
project (logger)

set (CMAKE_INSTALL_PREFIX /tools/utils)

if (NOT CMAKE_DEBUG_POSTFIX)
	set(CMAKE_DEBUG_POSTFIX "-d")
endif()

# Add library
add_library(logger logger.cpp)
target_include_directories (logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install
install(TARGETS logger DESTINATION lib)
install(FILES logger.hpp DESTINATION include)