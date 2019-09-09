cmake_minimum_required (VERSION 3.4)
project (leveld)

set (CMAKE_INSTALL_PREFIX /tools)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_GENERATOR_PLATFORM x64)

include_directories(/tools/include)

if (NOT CMAKE_DEBUG_POSTFIX)
	set(CMAKE_DEBUG_POSTFIX "-d")
endif()

# Add library
add_library(${PROJECT_NAME}
					LevelD.cpp
					Bytestream/BytestreamIn.cpp
					Bytestream/BytestreamOut.cpp
					Modules/ModuleMetadata.cpp
					Modules/ModuleMesh.cpp
					Modules/ModulePlayers.cpp
					Modules/ModuleItems.cpp
					Modules/ModuleNpcs.cpp
)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add testrunner
add_executable(testrunner
					Main.cpp
					Tests/TestMetadata.cpp
					Tests/TestMesh.cpp
					Tests/TestPlayers.cpp
					Tests/TestItems.cpp
					Tests/TestNpcs.cpp
					Tests/TestAll.cpp
)

find_library(CFG_LIB NAMES config)
TARGET_LINK_LIBRARIES(testrunner ${PROJECT_NAME} ${CFG_LIB})

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES LevelD.hpp DESTINATION include)