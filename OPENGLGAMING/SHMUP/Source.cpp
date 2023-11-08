#include <iostream>
#include <GL/glew.h>
#include "Triangle2D.h"
#include <SFML/Graphics.hpp>

#include "Camera.h"

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	sf::Window window(sf::VideoMode(1024, 1024,32), "ALAID", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setFramerateLimit(60);
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	camera.Position = glm::vec3(0.0f, 0.0f, 2.0f);
	camera.Front = glm::vec3(0.0f, 0.0f, -1.0f);
	glewExperimental = GL_TRUE;
	glewInit();
	/*auto* triangle = new Triangle2D();*/
	auto* scene = new Scene();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type ==
				sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
			camera.ProcessKeyboard(FORWARD, 0.01f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			camera.ProcessKeyboard(BACKWARD, 0.01f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
			camera.ProcessKeyboard(LEFT, 0.01f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			camera.ProcessKeyboard(RIGHT, 0.01f);
		/*triangle->viewMatrix = camera.GetViewMatrix();
		triangle->display();*/
		//triangle->Update(0.01f);
		scene->viewMatrix = camera.GetViewMatrix();
		scene->display();
		scene->Update(0.01f);
		window.display();
	}

	return 0;
}
