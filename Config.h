#pragma once
using namespace System; // This import is important to have the basic types
using namespace System::Drawing; // This import is important to have the basic types

// This is the basic config of the setup
// To make a simple setup, you only need to change this
// All the other files are the source, and mostly do not need to be modified

namespace XoverseSetup
{
	ref class Config
	{
	public:
		static String^ GameName = "Example Setup"; // The name of your game
		static Color BarColor = Color::FromArgb(245, 133, 13); // The top bar color
	};
}