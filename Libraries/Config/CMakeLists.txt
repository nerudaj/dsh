cmake_minimum_required (VERSION 3.4)
project (config)

# Export all symbols in dynamic library
set (CMAKE_INSTALL_PREFIX /tools/utils)

include_directories(/tools/utils/include)

if (NOT CMAKE_DEBUG_POSTFIX)
	set(CMAKE_DEBUG_POSTFIX "-d")
endif()

# Add library
add_library(${PROJECT_NAME} Args.cpp Csv.cpp Ini.cpp Item.cpp)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES Config.hpp Args.hpp Csv.hpp Ini.hpp Item.hpp DESTINATION include)