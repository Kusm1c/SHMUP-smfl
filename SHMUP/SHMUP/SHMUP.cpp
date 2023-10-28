#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <memory>

using namespace std;

int main()
{
	Game game;
	cout << "Starting game..." << endl;
	game.run();
	return 0;
}
