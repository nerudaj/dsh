cmake_minimum_required (VERSION 3.4)
project (strings)

# Export all symbols in dynamic library
set (CMAKE_INSTALL_PREFIX /tools/utils)

# Add library
add_library(strings Strings.cpp)
target_include_directories (strings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install
install(TARGETS strings DESTINATION lib)
install(FILES Strings.hpp DESTINATION include)