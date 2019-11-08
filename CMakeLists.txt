# dsh
cmake_minimum_required ( VERSION 3.0 )

## Project setup
project ( dsh )
set ( PROJECT_VERSION_MAJOR "1" )
set ( PROJECT_VERSION_MINOR "0" )
set ( PROJECT_VERSION_PATCH "0" )

## Add subdirectories as needed
add_subdirectory ( Libraries )

## Allow pushing test targets to ctest
enable_testing()

## Install few additional files
install(
	FILES
		changelog.txt
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

include ( CPack )
