-- ---------------------------------
-- Toni Barella
-- Inteligencia Artificial 3�
-- ESAT 2016-2019
-- Genie Project Configuration.
-- ---------------------------------
solution ("3IA_Solution" .. _ACTION)
 configurations { "Debug", "Release" }
 platforms { "x32", "x64" }
 location ("build")
 language "C"
 kind "ConsoleApp"
    language "C++"
    kind "ConsoleApp"
    projects = { "PR0_Base", "PR1_AStar" }
    for i, prj in ipairs(projects) do
        project (prj)
        targetname (prj)
        prj_path = "./build/" .. prj
        location (prj_path .. "/" .. _ACTION)
        includedirs {
            "./include/",
            "./deps/include",
            "./deps/include/SFML",
        }
        files {
            "./deps/include/*.h",
            "./deps/include/SFML/*.h",
        }
        defines { "_CRT_SECURE_NO_WARNINGS" }
        flags { "ExtraWarnings" }
        configuration "vs2015"
          windowstargetplatformversion "8.1"
        configuration "vs2017"
        --windowstargetplatformversion "10.0.15063.0"
        --windowstargetplatformversion "10.0.16299.0"
        --windowstargetplatformversion "10.0.17134.0"
        --windowstargetplatformversion "10.0.17134.471"
        windowstargetplatformversion "10.0.17763.0"
   configuration "Debug"
       defines { "DEBUG" }
        links { "./deps/lib/sfml-graphics-d", "./deps/lib/sfml-window-d", "./deps/lib/sfml-audio-d", "./deps/lib/sfml-system-d", "./deps/lib/sfml-network-d","opengl32",
        "user32","shell32","gdi32"}
       targetdir ("bin/Debug")
       targetsuffix "_d"
       objdir ("build/" .. "Debug")
       flags { "Symbols" }
   configuration "Release"
   links { "./deps/lib/sfml-graphics-s", "./deps/lib/sfml-window-s", "./deps/lib/sfml-audio-s", "./deps/lib/sfml-system-s", "./deps/lib/sfml-network-s","opengl32",
        "user32","shell32","gdi32"}
       targetdir ("bin/Release")
       objdir ("build/" .. "Release")
       flags { "Optimize" }
    end
    project "PR0_Base"
        files {
      "./src/main.cc",
      "./include/application.h",
      "./src/application.cc",
      "./include/agent.h",
      "./src/agent.cc",
      "./include/path.h",
      "./src/path.cc",
      "./include/app_manager.h",
      "./src/app_manager.cc"
    }
    project "PR1_AStar"
        files {
      "./src/astar_main.cc",
      "./include/astar_app.h",
      "./src/astar_app.cc",
      "./include/app_manager.h",
      "./src/app_manager.cc",
      "./include/astar.h",
      "./src/astar.cc"
    
}