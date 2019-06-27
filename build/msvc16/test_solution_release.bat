@echo off

set "PROJECT=jpp"
set "CONFIGURATION=Release"
set "SOLUTION_DIR=..\..\solutions\test_%PROJECT%_msvc16\%CONFIGURATION%"

@mkdir %SOLUTION_DIR%
@pushd %SOLUTION_DIR%

CMake -G "Visual Studio 16 2019" -A Win32 -S "%CD%\..\..\.." -DCMAKE_CONFIGURATION_TYPES:STRING="%CONFIGURATION%" -DCMAKE_BUILD_TYPE:STRING=%CONFIGURATION% -DJPP_TEST:BOOL=TRUE
CMake --build . --config %CONFIGURATION%
CTest -C %CONFIGURATION%

@popd

@echo on
@pause
