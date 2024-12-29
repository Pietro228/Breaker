#!/bin/bash
./premake.sh
make clean
make config=release

cp -r ./assets ./bin/Release