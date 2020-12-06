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
					Modules/ModuleNpcsItemsPlayers.cpp
					Modules/ModuleThings.cpp
					Modules/ModuleTriggers.cpp
)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install
install(
	TARGETS
		${PROJECT_NAME}
	DESTINATION
		lib
)

if (${MANDATORY_FOR_VISUAL_STUDIO})
	install(
		FILES
			${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROJECT_NAME}-d.lib
		DESTINATION
			lib
	)
endif()

install(
	FILES
		LevelD.hpp
	DESTINATION
		include
)

install(
	FILES
		LevelD.md
	DESTINATION
		docs
)

install(
	FILES
		_Bindings/EcmaScript6/leveld.js
		_Bindings/EcmaScript6/readme.md
	DESTINATION
		bindings/ecmascript6
)

# Tests
add_subdirectory ( Tests )