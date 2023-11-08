#pragma once
#include <glm/mat4x4.hpp>

#include "Scene.h"
class Triangle2D :
    public Scene
{
public:
	Triangle2D();
	~Triangle2D();
	void Update(float dt);
	void display();
	glm::mat4 translationMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);


private:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	GLuint shaderVertexProgram;
	GLuint shaderfragmentProgram;
	GLuint shaderProgram;
	unsigned int textureID;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	glm::mat4 mvp = glm::mat4(1.0f);
};

