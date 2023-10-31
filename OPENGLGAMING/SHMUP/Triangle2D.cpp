#include "Triangle2D.h"

#define GLSL(shader) "#version 330 core\n" #shader

char buffer[512];
GLint status;
Triangle2D::Triangle2D() : Scene()
{

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLfloat vertices[] = {
		-0.5f, 0.5f,
		0.5f, 0.5f,
		0.5f, -0.5f,
	};
	const GLchar* vertexShaderSource = GLSL(
		in vec2 gl_Position;
	void main()
	{
		gl_Position = vec4(position, 1.0f);
	}
	);

	const GLchar* fragmentShaderSource = GLSL(
		out vec4 outColor;
	void main()
	{
		outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
	             vertices, GL_STATIC_DRAW);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource,
	               nullptr);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource,
			               nullptr);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	positionAttrib = glGetAttribLocation(shaderProgram, "gl_Position");
	glEnableVertexAttribArray(positionAttrib);
	glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, GL_FALSE,sizeof(GLfloat) * 2, 0);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

	glGetShaderInfoLog(vertexShader, 512, nullptr, buffer);
}

Triangle2D::~Triangle2D()
{
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void Triangle2D::Update(float dt)
{
	Scene::Update(dt);
}

void Triangle2D::display()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(shaderProgram);
	Scene::display();
}
