set ( TESTRUNNER "testrunner_config" )

add_executable( ${TESTRUNNER}
	main.cpp
	ItemTests.cpp
	ArgsTests.cpp
	IniTests.cpp
	CsvTests.cpp
	Helper.cpp
)

target_link_libraries( ${TESTRUNNER}
	${PROJECT_NAME}
	strings
)

add_test ( NAME ${PROJECT_NAME} COMMAND ${TESTRUNNER} )
