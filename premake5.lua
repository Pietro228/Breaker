-- premake5.lua
workspace "Breaker"
   configurations { "Debug", "Release" }

project "Breaker"
   kind "ConsoleApp" -- WindowedApp / ConsoleApp
   language "C"
   targetdir "bin/%{cfg.buildcfg}"
   architecture "x86_64"  -- Default architecture

   filter "system:macosx"
      architecture "arm64"

   files { "include/**.h", "src/**.c" } -- "src/**.h", 

   includedirs {
      "libs/BeEngine/include",
      "include"
   }

   libdirs {
      "libs/BeEngine/lib"
   }

   links { "BeEngine" }
   linkoptions { "-rpath", "@executable_path/../../libs/BeEngine/lib" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
   
   filter {"system:macosx", "configurations:Debug"}
      buildoptions { "-fsanitize=address" }
      linkoptions { "-fsanitize=address" }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"