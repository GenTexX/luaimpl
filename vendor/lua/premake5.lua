project "lua"
	kind "StaticLib"
	language "C++"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
	files
	{
		"src/**.h",
		"src/**.c"
	}
	
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "on"
		
	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"