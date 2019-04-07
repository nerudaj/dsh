cmake_minimum_required (VERSION 3.4)
project (bs_testrunner)

# Add testrunner
add_executable(testrunner
            Main.cpp
            BytestreamIn.cpp
            BytestreamOut.cpp
)