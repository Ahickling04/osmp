#include "fileHandling.h"

#include <iostream>
#include <filesystem>

void testFunc(){
	std::cout << "This library is working\n";
}

int configCheck(){
	#if defined _WIN32
	const std::string os = "Windows";
	#elif defined (__linux__)
	const std::string os = "Linux";
	#else defined (__APPLE__)
	const std::string os = "Macos";
	#endif

	std::filesystem::path configPath;
	
	if(os == "Windows"){
		configPath = "C:/Users/%username%/AppData/Roaming/osmp";
		std::cout << "You're using windows";
	}
	else if(os == "Linux" || os == "Macos"){
		configPath = "~/.config/osmp";
		std::cout << "You're using GNU/Linux";
	}
	else{
		std::cout << "Where am i supposed to put the config files now :(";
		return -1;
	}
	return 0;
}

