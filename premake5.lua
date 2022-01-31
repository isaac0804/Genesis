workspace "Genesis"
	architecture "x64"
	configurations {"Debug", "Release", "Dist"}
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "Genesis/thirdparty/GLFW/include"
IncludeDir["Glad"] = "Genesis/thirdparty/GLAD/include"
IncludeDir["ImGui"] = "Genesis/thirdparty/ImGui"

group "Dependencies"
	include "Genesis/thirdparty/GLFW"
	include "Genesis/thirdparty/Glad"
	include "Genesis/thirdparty/ImGui"
group ""

project "Genesis"
	location "Genesis"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gspch.h"
	pchsource "Genesis/src/gspch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/thirdparty/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines 
		{
			"GS_PLATFORM_WINDOWS",
			"GS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			--("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "GS_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GS_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GS_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Genesis/thirdparty/spdlog/include",
		"Genesis/src"
	}

	links
	{
		"Genesis"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines 
		{
			"GS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GS_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "GS_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "GS_DIST"
		runtime "Release"
		optimize "On"
