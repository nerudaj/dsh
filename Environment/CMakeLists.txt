cmake_minimum_required ( VERSION 3.1 )

project ( dsh-environment )

install(
	FILES
		bootstrap.bat
		doomsh.cmd
		dsh.bat
		Scripts/unzip.vbs
		Scripts/wget.js
	DESTINATION
		install
)
