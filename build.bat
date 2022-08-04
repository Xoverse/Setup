@echo off

echo ##################
echo #  Evil Buddy's  #
echo # MSBuild Helper #
echo ##################

set /p PROJ="Project name (without ".vcxproj"): "

echo selected %PROJ%.vcxproj

echo.
echo 1. Release
echo 2. Debug

choice /C 12 /N
if ERRORLEVEL == 1 set configuration=Release
if ERRORLEVEL == 2 set configuration=Debug

echo selected %configuration%

echo.
echo 1. x86
echo 2. x64

choice /C 12 /N
if ERRORLEVEL == 1 set architecture=Win32
if ERRORLEVEL == 2 set architecture=x64

echo selected %architecture%
echo %PROJ%.vcxproj will be built in %configuration% for %architecture%, is this right ? [Y/N]

choice /C YN /N

if ERRORLEVEL == 2 exit

cls
echo msbuild %PROJ%.vcxproj /p:configuration = %configuration% /p:platform = %architecture%
echo.

msbuild %PROJ%.vcxproj /p:configuration = %configuration% /p:platform = %architecture%

echo.
echo Build completed, check above for errors.
pause