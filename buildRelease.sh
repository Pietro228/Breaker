#!/bin/bash
cp ../BeEngineC/bin/Release/libBeEngine.dylib ./libs/BeEngine/lib/libBeEngine.dylib
cp -r ./assets ./bin/Release

./premake.sh
make clean
make config=release