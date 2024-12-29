#!/bin/bash
mkdir -p ./libs/BeEngine/lib/

if [ -e "../BeEngineC/bin/Debug/libBeEngine.dylib" ]; then
    cp ../BeEngineC/bin/Debug/libBeEngine.dylib ./libs/BeEngine/lib/libBeEngine.dylib
else
    cp ../BeEngineC/bin/Debug/libBeEngine.so ./libs/BeEngine/lib/libBeEngine.so
fi

mkdir -p ./bin/Debug
cp -r ./assets ./bin/Debug

./premake.sh
make clean
make config=debug