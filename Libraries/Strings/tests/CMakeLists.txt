set ( TESTRUNNER "testrunner_strings" )

add_executable( ${TESTRUNNER} 
	main.cpp
)

target_link_libraries( ${TESTRUNNER}
	${PROJECT_NAME}
)

add_test ( NAME ${PROJECT_NAME} COMMAND ${TESTRUNNER} )