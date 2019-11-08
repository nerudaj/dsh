set ( TESTRUNNER "testrunner_config" )

add_executable( ${TESTRUNNER} 
	Main.cpp
	ItemTests.cpp
	ArgsTest.cpp
)

target_link_libraries( ${TESTRUNNER}
	${PROJECT_NAME}
	strings
)

add_test ( NAME ${PROJECT_NAME} COMMAND ${TESTRUNNER} ${CMAKE_CURRENT_SOURCE_DIR} )

set ( TESTRUNNER_OLD "testrunner_config_old" )

add_executable( ${TESTRUNNER_OLD} 
	_main.cpp
)

target_link_libraries( ${TESTRUNNER_OLD}
	${PROJECT_NAME}
	strings
)

add_test ( NAME ${PROJECT_NAME}_2 COMMAND ${TESTRUNNER_OLD} ${CMAKE_CURRENT_SOURCE_DIR} )