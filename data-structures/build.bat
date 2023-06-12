@echo off

mkdir ..\..\build
pushd ..\..\build

cl /EHsc -Zi ..\source\data-structures\main.cpp /I ..\source\data-structures\

popd
