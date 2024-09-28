@echo off

set "PROJECT=jpp"
set "CONFIGURATION=%1"
set "SOLUTION_DIR=..\..\solutions\%PROJECT%_msvc17\%CONFIGURATION%"

@mkdir %SOLUTION_DIR%
@pushd %SOLUTION_DIR%

CMake -G "Visual Studio 17 2022" -A Win32 -S "%CD%\..\..\.." -DCMAKE_CONFIGURATION_TYPES:STRING=%CONFIGURATION% -DCMAKE_BUILD_TYPE:STRING=%CONFIGURATION% -DJPP_TEST:BOOL=FALSE

@popd

@echo on