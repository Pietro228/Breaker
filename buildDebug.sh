#!/bin/bash

/premake.sh
make clean
make config=debug

cp -r ./assets ./bin/Debug