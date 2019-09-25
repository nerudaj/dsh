cmake_minimum_required (VERSION 3.4)

project (leveld)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Config")

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

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES LevelD.hpp DESTINATION include)

# Tests
add_subdirectory ( Tests )