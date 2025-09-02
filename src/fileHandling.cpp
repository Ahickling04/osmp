#include "fileHandling.h"

#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <fstream>
//#include <toml++/impl/table.hpp>
#include <toml++/toml.h>

void testFunc(){
	std::cout << "This library is working\n";
}



int configCheck(std::filesystem::path configPath){
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

	//std::filesystem::path configPath;	
	if(os == "Windows"){
		//std::cout << "You're using windows\n";
		std::filesystem::path homePath = std::getenv("USERPROFILE");
		//Does the config folder exist? if not create the folder
		
		//temp vairable to create the config variable
		std::filesystem::path configPath = homePath +="/appdata/local/osmp/";

		if(!std::filesystem::exists(configPath)){
			std::filesystem::create_directories(configPath);
			std::cout << "Config directory created: " << configPath << '\n';
			std::fstream(configPath += "/appdata/local/osmp/config.toml", std::ios::in);
		}
		else{
			std::cout << "Config folder already exists\n";
		}
	}
	else if(os == "Linux" || os == "Macos"){
		
		std::filesystem::path homePath = std::getenv("HOME");
		configPath = homePath +="/.config/osmp/";
		if(!std::filesystem::exists(configPath)){
			std::filesystem::create_directories(configPath);
			std::cout << "Config directory created: " << configPath << '\n';
			
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

int mkDefaults(std::filesystem::path configPath){
	/* what this function will do is generate some default settings that the prgram will load of first launch.
	 * this will be done in a TOML format so that it is easy for the end user to edit themselves
	 * It will also assume some defaults as well, like the audio driver, the location of the music folder.
	 * it Shouldn't be too hard.*/
	
	//create the Music path variable

	//create the TOML table
	toml::table config;
	
	//add values that will be tha main titles
	//config.insert("directories.music");
	


	return 0;
}

