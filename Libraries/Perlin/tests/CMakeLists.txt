cmake_minimum_required ( VERSION 3.1 )

set ( TGT_NAME "testrunner_${PROJECT_NAME}" )

add_executable ( ${TGT_NAME}
	Main.cpp
)

target_link_libraries ( ${TGT_NAME}
	${PROJECT_NAME}
)

add_test (
	NAME
		${TGT_NAME}
	COMMAND
		${TGT_NAME}
)