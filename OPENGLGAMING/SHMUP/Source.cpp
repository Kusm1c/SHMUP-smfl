#include <iostream>
#include <GL/glew.h>
#include "Triangle2D.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "ALAID");
	window.setFramerateLimit(60);
	glewExperimental = GL_TRUE;
	glewInit();
	auto* triangle = new Triangle2D();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type ==
				sf::Event::Closed)
				window.close();
		}
		window.clear();
		triangle->display();
		window.display();
	}

	return 0;
}
