#pragma once
#include <GL/glew.h>
#include "bmp.h"
#include <iostream>
#include <ostream>
#include <vcruntime.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#define GLSL(shader) "#version 330 core\n" #shader

class Scene
{
public:
	Scene();
	~Scene();
	virtual void Update(float dt);
	virtual void display();
};
