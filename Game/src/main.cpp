/* Copyright 2020 Samuel Dunny */
/* Main game */

#include "../inc/Game_Engine.h"
#include "../inc/MainMenu.h"

void runGame_Engine()
{
	Game_Engine game;
	while (game.running()) {
		game.Update();
		game.Render();
	}
}

void runMainMenu()
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
		runGame_Engine();
		break;

	case 1: //1 will be to exit and stop game
		break;

	default:
		break;
	}
}


//Begin Main
int main() {
	runMainMenu();
	return 0;
}