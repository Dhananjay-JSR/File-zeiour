@ECHO OFF
if exist build\ (
    goto run
) else (
    mkdir build
    goto run
)

:run
echo Building
@ECHO ON
Cmake -S . -B build/ -G "MinGW Makefiles"