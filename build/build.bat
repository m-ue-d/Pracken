@echo off
REM Load environment variables from .env.local
for /f "usebackq tokens=1,* delims==" %%A in ("../.env.local") do (
    set "%%A=%%B"
)

REM Run CMake commands in the same environment

cd ..

cmake --preset vcpkg -S . -B build

cd build

cmake --build .
