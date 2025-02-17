-- premake5.lua
workspace "Breaker"
   configurations { "Debug", "Release" }
   platforms { "x64", "x86_64", "ARM" }

project "Breaker"
   kind "ConsoleApp" -- WindowedApp / ConsoleApp
   language "C"
   targetdir "bin/%{cfg.buildcfg}/%{cfg.platform}"

   -- Set architecture
   filter "platforms:x86_64"
      architecture "x86_64"

   filter "platforms:ARM"
      architecture "ARM"

   filter "system:macosx"
      architecture "arm64"
      linkoptions { "-rpath", "@executable_path/../../libs/BeEngine/lib" }

   filter "system:windows"
      links { "kernel32", "user32", "gdi32", "ws2_32" }

   files { "include/**.h", "src/**.c" } -- "src/**.h", 

   includedirs {
      "libs/BeEngine/include",
      "include"
   }

   libdirs {
      "libs/BeEngine/lib"
   }

   links { "BeEngineC" }
   defines { "SDL_MAIN_HANDLED" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
   
   filter {"system:macosx", "configurations:Debug"}
      buildoptions { "-fsanitize=address" }
      linkoptions { "-fsanitize=address" }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"