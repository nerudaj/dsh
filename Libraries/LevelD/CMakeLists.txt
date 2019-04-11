cmake_minimum_required (VERSION 3.4)
project (leveld)

include_directories(/tools/utils/include)

# Add library
add_library(${PROJECT_NAME}
					LevelDHandler.cpp
					ParserModules/ParserModuleMesh.cpp
)
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Install
# install(TARGETS ${PROJECT_NAME} DESTINATION lib)
# install(FILES LevelDHandler.hpp DESTINATION include)