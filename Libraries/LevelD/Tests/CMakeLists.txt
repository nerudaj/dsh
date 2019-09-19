set ( TESTRUNNER "testrunner_leveld" )

#include_directories ( "${CMAKE_CURRENT_SOURCE_DIR}/../../Testrunner/include" )

add_executable( ${TESTRUNNER} 
	Main.cpp
	TestMetadata.cpp
	TestMesh.cpp
	TestPlayers.cpp
	TestItems.cpp
	TestNpcs.cpp
	TestAll.cpp
)

target_link_libraries( ${TESTRUNNER}
	${PROJECT_NAME}
	config
)

add_test ( NAME ${PROJECT_NAME} COMMAND ${TESTRUNNER} )