set ( TESTRUNNER "testrunner_leveld" )

add_executable( ${TESTRUNNER} 
	Main.cpp
	MetadataTests.cpp
	MeshTests.cpp
	ThingsTests.cpp
	AllTests.cpp
	BytestreamTests.cpp
)

target_link_libraries( ${TESTRUNNER}
	${PROJECT_NAME}
	config
)

add_test ( NAME ${PROJECT_NAME} COMMAND ${TESTRUNNER} )