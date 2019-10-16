cmake_minimum_required ( VERSION 3.4 )

if (NOT ("${CMAKE_GENERATOR}" MATCHES "MinGW Makefiles"))
	set (CMAKE_GENERATOR_PLATFORM "x64")
endif()

project ( dshlibs )

include_directories ( "Testrunner/include" )
include_directories ( "Catch" )

enable_testing()

set (CMAKE_INSTALL_PREFIX /tools)
set (CMAKE_CXX_STANDARD 17)

IF (MSVC)
	set (CMAKE_CXX_FLAGS "/EHsc")
ENDIF (MSVC)

if (NOT CMAKE_DEBUG_POSTFIX)
	set(CMAKE_DEBUG_POSTFIX "-d")
endif()

add_subdirectory ( Strings )
add_subdirectory ( Config )
add_subdirectory ( LevelD )
add_subdirectory ( Bitmap )
add_subdirectory ( Perlin )

include_directories ( Perlin )
include_directories ( Bitmap )

add_executable( perlin-test
	Perlin/perlin-test.cpp
)

target_link_libraries( perlin-test perlin bitmap )