cmake_minimum_required (VERSION 3.4)

project (leveld)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Config")

set ( BYTESTREAM_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/Bytestream/Bytestream.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Bytestream/SwapEndian.hpp"
)

set ( BYTESTREAM_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/Bytestream/BytestreamIn.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Bytestream/BytestreamOut.cpp"
)

set ( MODULES_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/Modules/Top.hpp"
)

set ( MODULES_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/Modules/ModuleMesh.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Modules/ModuleMetadata.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Modules/ModuleNpcsItemsPlayers.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Modules/ModulePaths.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Modules/ModuleThings.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Modules/ModuleTriggers.cpp"
)

set ( LEVELD_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/LevelD.hpp"
)

set ( LEVELD_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/LevelD.cpp"
)

# Add library
add_library(${PROJECT_NAME}
	${BYTESTREAM_HEADERS} ${BYTESTREAM_SOURCES}
	${MODULES_HEADERS} ${MODULES_SOURCES}
	${LEVELD_HEADERS} ${LEVELD_SOURCES}
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
		${LEVELD_HEADERS}
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