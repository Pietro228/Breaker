#!/bin/bash
mkdir -p ./libs/BeEngine/lib/

if [ -e "../BeEngineC/bin/Release/libBeEngine.dylib" ]; then
    cp ../BeEngineC/bin/Release/libBeEngine.dylib ./libs/BeEngine/lib/libBeEngine.dylib
else
    cp ../BeEngineC/bin/Release/libBeEngine.so ./libs/BeEngine/lib/libBeEngine.so
fi

mkdir -p ./bin/Release
cp -r ./assets ./bin/Release

./premake.sh
make clean
make config=release