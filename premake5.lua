workspace "Sigiri"

	configurations { 
		"Debug32", 
		"Release32",
		"Debug64", 
		"Release64" 
	}

   	filter "configurations:*32"
    	architecture "x86"

   	filter "configurations:*64"
      	architecture "x86_64"

    filter {}

outputDir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}";

project "Sigiri"
	location "Sigiri"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("int/" .. outputDir .. "/%{prj.name}")

	files {
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs {
		"%{prj.name}/"
	}

	filter "system:windows"
		systemversion "latest"
		defines "S_WINDOWS"

	filter "system:linux"
		systemversion "latest"
		defines "S_LINUX"

	filter "system:macosx"
		systemversion "latest"
		defines "S_MAC"
		
	filter "configurations:Debug*"
		defines "S_DEBUG"
		symbols "On"

	filter "configurations:Release*"
		defines "S_RELEASE"
		optimize "On"