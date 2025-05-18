#include "fileHandling.h"

#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <fstream>

void testFunc(){
	std::cout << "This library is working\n";
}

int configCheck(){
	/*The following code is to make check what operating system the ser is on
	 * then checking to see if the user has a config directory in ither .config (Linux & Macos)
	 * or in AppData (Windows). currently exprencing an issue saying that there is a config file
	 * within my file system however i cannot see it anywhere no matter how i check.
	 * current test happening rn is seeing if the app staying open means that the directory will still
	 * exist. 
	 */
	
	#if defined _WIN32
	const std::string os = "Windows";
	#elif defined (__linux__)
	const std::string os = "Linux";
	#elif defined (__APPLE__)
	const std::string os = "Macos";
	#endif

	std::filesystem::path configPath;	
	if(os == "Windows"){
		//std::cout << "You're using windows\n";
		configPath = std::getenv("HOME/appdata/local/osmp/");
		//Does the config folder exist? if not create the folder
		if(!std::filesystem::exists(configPath)){
			std::filesystem::create_directories(configPath);
			std::cout << "Config directory created: " << configPath << '\n';
			std::fstream("~/config/osmp/config.txt", std::ios::in);
		}
		else{
			std::cout << "Config folder already exists\n";
		}
	}
	else if(os == "Linux" || os == "Macos"){
		
		configPath = std::getenv("HOME");
		std::cout << configPath;
		//std::cout << "You're using GNU/Linux\n";
		if(!std::filesystem::exists(configPath += "/.config/osmp")){
			std::filesystem::create_directories(configPath);
			std::cout << "Config directory created: " << configPath << '\n';
			std::fstream(configPath += "config.txt", std::ios::in);
		}
		else {
			std::cout << "Config folder already exists\n";
		}
	}
	else{
		std::cout << "Where am i supposed to put the config files now :'(";
		return -1;
	}
	return 0;
	
	
	
}

