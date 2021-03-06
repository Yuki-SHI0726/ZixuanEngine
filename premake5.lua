workspace "ZixuanEngine"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"      -- Shipping
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Toolset/GLFW/include"
IncludeDir["Glad"] = "Toolset/Glad/include"
IncludeDir["ImGui"] = "Toolset/imgui"
IncludeDir["ImGuiBackends"] = "Toolset/imgui/backends"

include "Toolset/GLFW"
include "Toolset/Glad"
include "Toolset/imgui"

project "ZixuanEngine"
    location "ZixuanEngine"
    kind "SharedLib"
    language "C++"

    targetdir ("Builds/" .. outputdir .. "/%{prj.name}")
    objdir ("Builds/" .. outputdir .. "/%{prj.name}")

    pchheader "zepch.h"
    pchsource "ZixuanEngine/Source/Core/zepch.cpp"

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
    }

    includedirs
    {
        "ZixuanEngine/Source",
        "ZixuanEngine/Source/Core",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ImGuiBackends}",
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "ZE_PLATFORM_WINDOWS",
            "ZE_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
        }

    filter "configurations:Debug"
        defines "ZE_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "ZE_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "ZE_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("Builds/" .. outputdir .. "/%{prj.name}")
    objdir ("Builds/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/Source/**.h",
        "%{prj.name}/Source/**.cpp",
    }

    includedirs
    {
        "ZixuanEngine/Source",
        "ZixuanEngine/Source/Core",
    }

    links
    {
        "ZixuanEngine"
    }

    filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "ZE_PLATFORM_WINDOWS",
    }

    postbuildcommands
    {
        "xcopy \"$(SolutionDir)Builds\\" .. outputdir .. "\\ZixuanEngine\\*.dll\"" .. " \"$(OutDir)\"  /d /i /y"
    }

    filter "configurations:Debug"
        defines "ZE_DEBUG"
        defines "ZE_ENABLE_ASSERTS"
        symbols "On"

    filter "configurations:Release"
        defines "ZE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "ZE_DIST"
        optimize "On"