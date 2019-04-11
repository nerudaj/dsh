cmake_minimum_required (VERSION 3.4)
project (jsbloat)

set (CMAKE_INSTALL_PREFIX /tools/utils)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

include_directories(/tools/utils/include)

add_executable(${PROJECT_NAME} Main.cpp)

find_library(LOG_LIB NAMES logger)
find_library(CFG_LIB NAMES config)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LOG_LIB} ${CFG_LIB})

install(TARGETS ${PROJECT_NAME})