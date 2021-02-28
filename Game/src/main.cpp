/* Copyright 2020 Samuel Dunny */
/* Main game */

#include "../inc/Game_Engine.h"
#include "../inc/MainMenu.h"

bool runGame_Engine()
{
	Game_Engine game;
	while (game.running()) {
		game.Update();
		game.Render();
	}
	return true; //Default code placeholder to exit to Main Menu
}

bool runMainMenu()
{
	MainMenu mainMenu;
	int mainMenuExitCode = -1;
	while (mainMenu.running())
	{
		mainMenuExitCode = mainMenu.update();
		mainMenu.render();
	}
	switch (mainMenuExitCode) //Will return what to run
	{
	case 0: //0 will be to run Game engine
		if (runGame_Engine()); {
			return true;
		}
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