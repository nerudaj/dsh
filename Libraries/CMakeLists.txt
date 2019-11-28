cmake_minimum_required ( VERSION 3.4 )

project ( dshlibs )

enable_testing()

if (NOT CMAKE_DEBUG_POSTFIX)
	set(CMAKE_DEBUG_POSTFIX "-d")
endif()

add_subdirectory ( Strings )
add_subdirectory ( Config )
add_subdirectory ( LevelD )
add_subdirectory ( Bitmap )
