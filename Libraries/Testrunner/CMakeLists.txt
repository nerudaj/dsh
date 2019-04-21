cmake_minimum_required ( VERSION 2.8) 

set (CMAKE_INSTALL_PREFIX /tools/utils)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

# Install only header
install(FILES Test.hpp DESTINATION include)

# Buld testrunner demonstration demo
project ( testrunner_demo )

add_executable(${PROJECT_NAME} Main.cpp)