cmake_minimum_required (VERSION 3.4)
project (bitmap)

# Export all symbols in dynamic library
set (CMAKE_INSTALL_PREFIX /tools/utils)

include_directories(/tools/utils/include)

# Add library
add_library(${PROJECT_NAME} Bitmap.cpp)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES Bitmap.hpp DESTINATION include)