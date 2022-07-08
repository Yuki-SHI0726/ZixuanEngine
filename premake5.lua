workspace "ZixuanEngine"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"      -- Shipping
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "ZE_PLATFORM_WINDOWS",
            "ZE_BUILD_DLL"
        }
    
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../Builds/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "ZE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "ZE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "ZE_DIST"
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

    filter "configurations:Debug"
        defines "ZE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "ZE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "ZE_DIST"
        optimize "On"