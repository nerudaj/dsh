cmake_minimum_required ( VERSION 3.1 )

project ( dsh-environment )

install(
	FILES
		bootstrap.bat
		doomsh.cmd
		dsh.bat
		unzip.vbs
		unzip.bat
		wget.js
		wget.bat
	DESTINATION
		install
)
