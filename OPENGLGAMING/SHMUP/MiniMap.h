#pragma once
#include "Scene.h"

class MiniMap : public Scene
{
public:
	MiniMap();
	~MiniMap();

	void Update(float dt) override;
	void display() override;

private:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	GLuint textureID;
	unsigned int width, height;

	GLuint vertexShaderProgram;
	GLuint fragmentShaderProgram;
	GLuint shaderProgram;

};

