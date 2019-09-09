cmake_minimum_required (VERSION 3.4)
project (jsbloat)

set (CMAKE_INSTALL_PREFIX /tools)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

include_directories(/tools/include)

add_executable(${PROJECT_NAME} Main.cpp)

find_library(CFG_LIB NAMES config)
find_library(STR_LIB NAMES strings)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CFG_LIB} ${STR_LIB})

install(TARGETS ${PROJECT_NAME})