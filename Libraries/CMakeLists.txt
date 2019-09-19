cmake_minimum_required ( VERSION 3.4 )

set (CMAKE_INSTALL_PREFIX /tools)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set (CMAKE_CXX_STANDARD 17)
#set (CMAKE_GENERATOR_PLATFORM x64)

if (NOT CMAKE_DEBUG_POSTFIX)
	set(CMAKE_DEBUG_POSTFIX "-d")
endif()

enable_testing()

project ( dshlibs )

add_subdirectory ( Strings )
add_subdirectory ( Config )
add_subdirectory ( LevelD )
add_subdirectory ( Bitmap )