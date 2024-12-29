#!/bin/bash
cp ../BeEngineC/bin/Debug/libBeEngine.dylib ./libs/BeEngine/lib/libBeEngine.dylib
cp -r ./assets ./bin/Debug

./premake.sh
make clean
make config=debug