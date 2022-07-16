workspace "luaimpl"
	architecture "x64"
	startproject "sandbox"
	
	configurations
	{
		"Debug",
		"Release"
	}
	
outputDir = "%{cfg.buildcfg}-%{cfg.architecture}"
	
includeDir = {}
libDir = {}

--IMGUI
includeDir["LUA"] = "vendor/lua/src"

include "vendor/lua"

project "luaimpl"
	location "luaimpl"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{includeDir.LUA}"
	}
	
	links
	{	
		"lua"
	}

	defines {
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines{
			"NOMINMAX",
			"_CRT_SECURE_NO_WARNINGS"
		}




