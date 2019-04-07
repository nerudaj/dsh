cmake_minimum_required (VERSION 3.4)
project (leveld)

set (CMAKE_INSTALL_PREFIX C:\\tools\\utils)

include_directories(/tools/utils/include)

# Add library
add_library(${PROJECT_NAME}
					LevelD.cpp
					Bytestream/BytestreamIn.cpp
					Bytestream/BytestreamOut.cpp
					Modules/ModuleMetadata.cpp
					Modules/ModuleMesh.cpp
					Modules/ModulePlayers.cpp
)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add testrunner
add_executable(testrunner Main.cpp)

find_library(LOG_LIB NAMES logger)
find_library(CFG_LIB NAMES config)
TARGET_LINK_LIBRARIES(testrunner ${LOG_LIB} ${PROJECT_NAME} ${CFG_LIB})

# Install
# install(TARGETS ${PROJECT_NAME} DESTINATION lib)
# install(FILES LevelDHandler.hpp DESTINATION include)