#pragma once
#include <GL/glew.h>
#include "bmp.h"
#include <iostream>
#include <ostream>
#include <vcruntime.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#define GLSL(shader) "#version 330 core\n" #shader

class Scene
{
public:
	Scene();
	~Scene();
	virtual void Update(float dt);
	virtual void display();
	glm::mat4 translationMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);

protected:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLint positionAttrib;
	unsigned int NUM_STRIPS_REQUIRED;
	unsigned int VERTICES_PER_STRIP;

	unsigned int textureID;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	glm::mat4 mvp = glm::mat4(1.0f);
};
