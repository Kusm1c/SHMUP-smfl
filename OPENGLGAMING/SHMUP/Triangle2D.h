#pragma once
#include "Scene.h"
class Triangle2D :
    public Scene
{
public:
	Triangle2D();
	~Triangle2D();
	void Update(float dt);
	void display();

private:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	GLuint shaderVertexProgram;
	GLuint shaderfragmentProgram;
	GLuint shaderProgram;
};

