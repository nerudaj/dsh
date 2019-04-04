cmake_minimum_required (VERSION 3.4)
project (config)

# Export all symbols in dynamic library
set (CMAKE_INSTALL_PREFIX /tools/utils)

include_directories(/tools/utils/include)

# Add library
add_library(config Args.cpp Csv.cpp Ini.cpp Item.cpp)
target_include_directories (config PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install
install(TARGETS config DESTINATION lib)
install(FILES Config.hpp Args.hpp Csv.hpp Ini.hpp Item.hpp DESTINATION include)