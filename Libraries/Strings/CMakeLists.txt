cmake_minimum_required (VERSION 3.4)

project (strings)

# Add library
add_library( ${PROJECT_NAME} 
	Strings.cpp
)

target_include_directories ( ${PROJECT_NAME} 
	PUBLIC 
		${CMAKE_CURRENT_SOURCE_DIR}
)

# Install
install(
	TARGETS      ${PROJECT_NAME} 
	DESTINATION  lib
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
		Strings.hpp 
	DESTINATION 
		include
)

# Tests
add_subdirectory ( tests )