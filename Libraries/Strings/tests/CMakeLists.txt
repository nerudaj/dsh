set ( TESTRUNNER "testrunner_strings" )

include_directories ( "${CMAKE_CURRENT_SOURCE_DIR}/../../Testrunner/include" )

add_executable( ${TESTRUNNER} 
	main.cpp
)

target_link_libraries( ${TESTRUNNER}
	${PROJECT_NAME}
)

add_test ( NAME ${PROJECT_NAME} COMMAND ${TESTRUNNER} )