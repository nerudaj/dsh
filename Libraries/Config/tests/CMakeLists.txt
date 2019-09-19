set ( TESTRUNNER "testrunner_config" )

include_directories ( "${CMAKE_CURRENT_SOURCE_DIR}/../../Testrunner/include" )

add_executable( ${TESTRUNNER} 
	main.cpp
)

target_link_libraries( ${TESTRUNNER}
	${PROJECT_NAME}
	strings
)

add_test ( NAME ${PROJECT_NAME} COMMAND ${TESTRUNNER} ${CMAKE_CURRENT_SOURCE_DIR} )