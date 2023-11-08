#include <iostream>
#include <GL/glew.h>
#include "Triangle2D.h"
#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Player.h"
#include "Terrain.h"

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	sf::RenderWindow window(sf::VideoMode(1024, 1024,32), "ALAID", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setFramerateLimit(60);
	Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));
	camera.Position = glm::vec3(0.5f, 0.25f, 3.0f);
	camera.Front = glm::vec3(0.0f, 0.1f, -1.0f);
	glewExperimental = GL_TRUE;
	glewInit();
	// Triangle2D* triangle = new Triangle2D();
	Terrain* scene = new Terrain();
	Player player(glm::vec3(0.0f, 1.0f, 3.0f), 0.1f);
	scene->scaleMatrix = glm::scale(scene->scaleMatrix, glm::vec3(2.5f));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type ==
				sf::Event::Closed)
				window.close();
		}
		camera.ProcessKeyboard(FORWARD, 0.001f);
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		// 	camera.ProcessKeyboard(FORWARD, 0.01f);
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		// 	camera.ProcessKeyboard(BACKWARD, 0.01f);
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		// 	camera.ProcessKeyboard(LEFT, 0.01f);
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		// 	camera.ProcessKeyboard(RIGHT, 0.01f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			camera.ProcessKeyboard(UP, 0.01f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
			camera.ProcessKeyboard(DOWN, 0.01f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			camera.ProcessMouseMovement(-10.0f, 0.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			camera.ProcessMouseMovement(10.0f, 0.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			camera.ProcessMouseMovement(0.0f, 10.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			camera.ProcessMouseMovement(0.0f, -10.0f);

		player.position = camera.Position;

		if (player.checkCollision(*scene)) {
			std::cout << "Death!" << std::endl;
		}
		scene->viewMatrix = camera.GetViewMatrix();
		scene->Update(0.01f);
		scene->display();
		window.display();
	}

	return 0;
}
