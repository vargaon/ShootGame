#include "Game.hpp"

using namespace sf;

int main()
{
   
	Game game;

	while (game.IsRunning())
	{
		game.Update();
		game.Render();
	}

	return 0;
}