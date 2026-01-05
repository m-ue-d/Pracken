@echo off
setlocal EnableDelayedExpansion

cmake --preset gcc -S . -B build -DCMAKE_BUILD_TYPE=Debug -DDESKTOP=ON

cmake --build build