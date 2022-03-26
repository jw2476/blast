
workspace "blast"
   configurations { "Debug", "Release" }


project "blast"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
    
   targetdir "bin"

   files { "src/**.h", "src/**.cpp" }

   includedirs {
      "vendor/spdlog/include",
      "vendor/raylib/src",
      "src",
      os.outputof("llvm-config --includedir")
   }

   links {
      "raylib",
      "pthread",
      "GL", 
      "m", 
      "dl", 
      "rt", 
      "X11"
   }

   linkoptions {
      "`llvm-config --libs core support x86asmparser x86codegen`",
      "`llvm-config --system-libs core support x86asmparser x86codegen`"
   }

   libdirs {
      "`llvm-config --libdir`"
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

include "./vendor/raylib/raylib"