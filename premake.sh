cp -r ../BeEngine/include/*.h ./libs/BeEngine/include
cp -r ../BeEngine/include/components/*.h ./libs/BeEngine/include
cp -r ../BeEngine/include/ui/*.h ./libs/BeEngine/include
cp -r ../BeEngine/include/ui/components/*.h ./libs/BeEngine/include
cp -r ../BeEngine/libs/SDL2/include/*.h ./libs/BeEngine/include

premake5 gmake2