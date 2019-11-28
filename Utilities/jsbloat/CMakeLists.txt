cmake_minimum_required (VERSION 3.4)
project (jsbloat)

set (CMAKE_INSTALL_PREFIX /tools)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

include_directories(/tools/include)

add_executable(${PROJECT_NAME} Main.cpp)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} config strings)

install(TARGETS ${PROJECT_NAME})