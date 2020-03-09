#include "Game.h"

int main(int argc, char* args[])
{
	//Create the main game class
	Game game;

	//INIT
	if (!game.Init()) return -1;


	//LOOP
	bool end = false;

	while (!end)
	{
		//Input & Update
		end = game.Update();

		//Render
		game.Draw();
	}

	//CLEANUP
	game.Release();


	return 0;
}