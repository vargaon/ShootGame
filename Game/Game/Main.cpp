#include "Game.hpp"

using namespace sf;

int main()
{
	Game game;

	while (game.IsRunning())
	{
		game.update();
		game.Render();
	}

	return 0;
}