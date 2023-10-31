#pragma once
#include <GL/glew.h>

class Scene
{
public:
	Scene();
	~Scene();
	virtual void Update(float dt);
	virtual void display();

protected:
		GLuint vao;
		GLuint vbo;
		/*const GLchar* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec2 position;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(position.x, 1.0);\n"
			"}\0";*/
		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint shaderProgram;
		GLint positionAttrib;
};
