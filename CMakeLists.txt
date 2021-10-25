# dsh
cmake_minimum_required ( VERSION 3.0 )

if (NOT ("${CMAKE_GENERATOR}" MATCHES "MinGW Makefiles"))
	if (NOT ("${CMAKE_GENERATOR}" MATCHES "Unix Makefiles"))
		set (CMAKE_GENERATOR_PLATFORM "x64")
		set ( BUILD_SYSTEM "vc16-64-bit" )
	else()
		set ( BUILD_SYSTEM "ubuntu" )
	endif()
else()
	# This could be x64 if build with mingw64 but I don't support mingw64 at this time
	set ( BUILD_SYSTEM "mingw32" )
endif()

set (CMAKE_INSTALL_PREFIX /tools)
set (CMAKE_CXX_STANDARD 17)

IF (MSVC)
	set (CMAKE_CXX_FLAGS "/EHsc")
ENDIF (MSVC)

## Project setup
project ( dsh )
set ( PROJECT_VERSION_MAJOR "1" )
set ( PROJECT_VERSION_MINOR "7" )
set ( PROJECT_VERSION_PATCH "0" )

## Catch2
include ( ExternalProject )
ExternalProject_Add( catch2
	URL                 "https://github.com/catchorg/Catch2/releases/download/v2.10.2/catch.hpp"
	DOWNLOAD_DIR        "${CMAKE_CURRENT_BINARY_DIR}/catch2"
	DOWNLOAD_NO_EXTRACT true
	CONFIGURE_COMMAND   ""
	BUILD_COMMAND       ""
	INSTALL_COMMAND     ""
)

include_directories ( "${CMAKE_CURRENT_BINARY_DIR}/catch2" )

## Add subdirectories as needed
add_subdirectory ( Libraries )
add_subdirectory ( Utilities )
add_subdirectory ( Environment )

## Allow pushing test targets to ctest
enable_testing()

## Install few additional files
install(
	FILES
		changelog.txt
	DESTINATION
		"."
)

install(
	FILES
		Readme.md
	DESTINATION
		"."
)

## Packaging
set ( CPACK_GENERATOR "ZIP" )

set ( CPACK_PACKAGE_DESCRIPTION_SUMMARY "Development C++ libraries and tools for Windows" )
set ( CPACK_PACKAGE_DESCRIPTION_FILE    "${CMAKE_CURRENT_SOURCE_DIR}/Readme.md" )
set ( CPACK_PACKAGE_VERSION_MAJOR       "${PROJECT_VERSION_MAJOR}" )
set ( CPACK_PACKAGE_VERSION_MINOR       "${PROJECT_VERSION_MINOR}" )
set ( CPACK_PACKAGE_VERSION_PATCH       "${PROJECT_VERSION_PATCH}" )
set ( CPACK_PACKAGE_FILE_NAME           "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}-${BUILD_SYSTEM}" )

include ( CPack )
