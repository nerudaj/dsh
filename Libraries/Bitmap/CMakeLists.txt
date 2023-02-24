cmake_minimum_required (VERSION 3.4)

project (bitmap)

# Add library
add_library( ${PROJECT_NAME}
	Bitmap.cpp 
	Palette.cpp 
	RawHeaders.cpp 
	IO.cpp
)

target_include_directories ( ${PROJECT_NAME} 
	PUBLIC 
		${CMAKE_CURRENT_SOURCE_DIR}
)

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

if (${MANDATORY_FOR_VISUAL_STUDIO})
	install(
		FILES
			"${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROJECT_NAME}-d.lib"
			"${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROJECT_NAME}-d.pdb"
		DESTINATION
			lib
	)
endif()

install(FILES Bitmap.hpp DESTINATION include)

# Add executable
add_subdirectory ( tests )