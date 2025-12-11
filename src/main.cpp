#include "fileHandling.h"

#include <iostream>
#include <filesystem>

int main(){
	//variables
	bool appStatus = true;
	char closeOption;

	while(appStatus == true){
		//A test toi see whether the directory stays open while the app is running.
		//because for some reason its saying that the directory exists when i cannot find it within my file system

		//this code should only run once... SHOULD being the operative word here.
		for(int i = 0; i < 1; i++){
			std::filesystem::path configPath;
			configCheck(configPath);
			std::cout << "Just some experimental code, nothing to see here\n";
			
			//Basic CLI exit code, should repeat after a invalid response or by saying no
			std::cout << "Would you like to exit the application?\n";
			std::cin >> closeOption;
			if(closeOption == 'y'){
				appStatus = false;
			}
			else if(closeOption == 'n'){
				i = 0;
			}
			else{
				std::cout << "That was not an option\n";
				i=0;
			}
		};

	};

}
