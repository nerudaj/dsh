cmake_minimum_required (VERSION 3.4)

project (config)

# Dependency on libstrings
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../Strings")

# Add library
add_library( ${PROJECT_NAME}
	Args.cpp
	Csv.cpp
	Ini.cpp
	Item.cpp
)

target_include_directories ( ${PROJECT_NAME}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)

# Install
install(
	TARGETS      config
	DESTINATION  lib
)

install(
	FILES
		Config.hpp
		Args.hpp
		Csv.hpp
		Ini.hpp
		Item.hpp
	DESTINATION
		include
)

# Tests
add_subdirectory ( tests )
