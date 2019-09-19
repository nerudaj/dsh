set ( TESTRUNNER "testrunner_bitmap" )

add_executable( ${TESTRUNNER} 
	Main.cpp
)

target_link_libraries( ${TESTRUNNER}
	${PROJECT_NAME}
)

add_test ( NAME ${PROJECT_NAME} COMMAND ${TESTRUNNER} )