mkdir -p ./libs/BeEngine/include

cp -r ../BeEngineC/include/*.h ./libs/BeEngine/include
cp -r ../BeEngineC/include/components/*.h ./libs/BeEngine/include
cp -r ../BeEngineC/include/ui/*.h ./libs/BeEngine/include
cp -r ../BeEngineC/include/ui/components/*.h ./libs/BeEngine/include
cp -r ../BeEngineC/libs/SDL2/include/*.h ./libs/BeEngine/include

premake5 gmake2