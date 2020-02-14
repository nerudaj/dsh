cmake_minimum_required ( VERSION 3.16 )

project ( leveld-migration-tool )

set (CMAKE_INSTALL_PREFIX /tools)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

include_directories(../../Libraries/Config)
include_directories(../../Libraries/LevelD)

add_executable ( ${PROJECT_NAME}
    Main.cpp
)

target_link_libraries ( ${PROJECT_NAME} strings config leveld )

install(
    TARGETS              ${PROJECT_NAME}
    RUNTIME DESTINATION  bin
)