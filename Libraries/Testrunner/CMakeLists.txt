cmake_minimum_required ( VERSION 2.8) 

project ( testrunner )

set (CMAKE_INSTALL_PREFIX /tools/utils)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set (CMAKE_GENERATOR_PLATFORM x86)

# Install only header
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
install(TARGETS ${PROJECT_NAME} DESTINATION include)
install(FILES include/Test.hpp DESTINATION include)

add_subdirectory(demo)