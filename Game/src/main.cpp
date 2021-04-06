/* Copyright 2020 Samuel Dunny */
/* Main game */

#include "../inc/Game_Engine.h"
#include "../inc/MainMenu.h"
//#include "../inc/Audio.hpp

// responsible for creating game and running it
bool runGame_Engine(bool inCheatMode) {
	if (inCheatMode) std::cout << "-----GAME IN CHEAT MODE-----" << std::endl;
	Game_Engine game(inCheatMode);
	while (game.running()) {
		game.Update();
		game.Render();
	}
	return true; //Default code placeholder to exit to Main Menu
}

// responsible for running main menu (and subsequently Game)
bool runMainMenu() {
	
	//sf::Music music;
	music.setPlayingOffSet(sf::seconds(3));
	music.setVolume(20);
	
	if (!music.openFromFile("MainMusic.wav"))

	{
		std::cout << "ERROR" << std::endl;
	}

	sf::Music music;
	music.setBuffer(buffer);
	music.play();
	
	MainMenu mainMenu;
	int mainMenuExitCode = -1;
	while (mainMenu.running()) {
		mainMenuExitCode = mainMenu.update();
		mainMenu.render();
	}
	switch (mainMenuExitCode) //Will return what to run
	{
	case 0: //0 will be to run Game engine
		if (runGame_Engine(mainMenu.inCheatMode())) {
			return true;
		}
		return false;
		break;

	case 1: //1 will be to exit and stop game
		return false;
		break;

	default:
		break;
	}
	return false;
}

//Begin Main
int main() {
	while (runMainMenu()) {};
	return 0;
}
