@echo off

mkdir ..\..\build\word-salad
pushd ..\..\build\word-salad

cl /EHsc /FAsc -Zi ..\..\source\word-salad\word-salad.cpp

popd
