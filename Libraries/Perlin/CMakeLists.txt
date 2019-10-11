cmake_minimum_required ( VERSION 3.1 )

project ( perlin )

add_library ( ${PROJECT_NAME} STATIC
	Math.cpp
	Convert.cpp
	VectorMath.cpp
	#RawNoiseGenerator.cpp
)

target_include_directories ( ${PROJECT_NAME} 
	PUBLIC 
		${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory ( tests )