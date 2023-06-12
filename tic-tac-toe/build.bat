@echo off

mkdir ..\..\build\tic-tac-toe
pushd ..\..\build\tic-tac-toe

set files=..\..\source\tic-tac-toe\tic-tac-toe.cpp
set files=%files% ..\..\source\tic-tac-toe\game.cpp

cl /EHsc /FAsc -Zi %files% /I ..\..\source\tic-tac-toe\ user32.lib

popd
