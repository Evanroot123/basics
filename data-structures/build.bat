@echo off

mkdir ..\..\build
pushd ..\..\build

set files=..\source\data-structures\main.cpp
set files=%files% ..\source\data-structures\linked-list-tests.cpp

cl /EHsc /FAsc -Zi %files% /I ..\source\data-structures\ user32.lib

popd
