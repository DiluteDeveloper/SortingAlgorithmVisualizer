
outputdir = "%{cfg.buildcfg}"




workspace "SortingAlgorithmVisualizer"
    location "../../"
    configurations { "Debug", "Release" }
    platforms "Win64"
    startproject "SortingAlgorithmVisualizer"
    debugdir "../../"

project "SortingAlgorithmVisualizer"
    kind "ConsoleApp"
    language "C++"
    system "Windows"
    cppdialect "C++20"
    systemversion "latest"
    debugformat "c7"

    links {"glad.lib", "glfw3.lib"}

    location ("%{wks.location}/%{prj.name}/")
    targetdir ("$(SolutionDir)bin/" .. outputdir .. "/")
    objdir ("$(SolutionDir)bin/" .. outputdir .. "/int/")
    debugdir "%{prj.location}"

    filter "configurations:Debug"
        symbols "On"
        optimize "Off"
        includedirs {"$(ProjectDir)src", "$(SolutionDir)dependencies/debug", "$(SolutionDir)dependencies/hybrid"}
        files { "%{prj.location}/src/**.cpp", "%{wks.location}/dependencies/hybrid/**.cpp", "%{wks.location}/dependencies/debug/**.cpp",
            "%{prj.location}/src/**.h", "%{wks.location}/dependencies/hybrid/**.h", "%{wks.location}/dependencies/debug/**.h"}
        libdirs "%{wks.location}/dependencies/debug/**"


    filter "configurations:Release"
        symbols "Off"
        optimize "On"
        includedirs {"$(ProjectDir)src", "$(SolutionDir)dependencies/release", "$(SolutionDir)dependencies/hybrid"}
        files { "%{prj.location}/src/**.cpp", "%{wks.location}/dependencies/hybrid/**.cpp", "%{wks.location}/dependencies/release/**.cpp",
            "%{prj.location}/src/**.h", "%{wks.location}/dependencies/hybrid/**.h", "%{wks.location}/dependencies/release/**.h"}

        libdirs "%{wks.location}/dependencies/release/**"