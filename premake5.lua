include "./vendor/premake/premake_customization/solution_items.lua"

workspace "SillyLang"
	architecture "x86_64"
	startproject "SillyLang"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Core"
	include "SillyLang"
group ""
