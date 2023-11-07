#include "Triangle2D.h"

#include <vcruntime.h>

#define GLSL(shader) "#version 330 core\n" #shader

Triangle2D::Triangle2D() : Scene()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//GLfloat vertices[] = {
	//	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0, // Vertex 1 (X, Y, Z, R, G, B)
	//	0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0, // Vertex 2 (X, Y, Z, R, G, B)
	//	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0, // Vertex 3 (X, Y, Z, R, G, B)

	//	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0, // Vertex 1 (X, Y, Z, R, G, B)
	//	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0, // Vertex 3 (X, Y, Z, R, G, B)
	//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0, // Vertex 4 (X, Y, Z, R, G, B)
	//};
	//same as above but make a cube
	GLfloat vertices[] = {
		//front
		-0.5f,	0.5f, 0.5f, 0.0f, 1.0f, 0.0, // Vertex 1 (X, Y, Z, R, G, B)
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0, // Vertex 2 (X, Y, Z, R, G, B)
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0, // Vertex 3 (X, Y, Z, R, G, B)
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0, // Vertex 4 (X, Y, Z, R, G, B)
		//back
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0, // Vertex 1 (X, Y, Z, R, G, B)
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0, // Vertex 2 (X, Y, Z, R, G, B)
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0, // Vertex 3 (X, Y, Z, R, G, B)
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0, // Vertex 4 (X, Y, Z, R, G, B)
	};

	//GLuint indices[] = {
	//	0, 1, 2, // Triangle 1
	//	0, 2, 3 // Triangle 2
	//};

	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
	//             vertices, GL_STATIC_DRAW);

	////const GLchar* vertexShaderSource = "#version 330 core\n"
	////	"in vec2 position;\n"
	////	"void main()\n"
	////	"{\n"
	////	"gl_Position = vec4(position.x, position.y, 0.0, 1.0);\n"
	////	"}\0";

	//const GLchar* vertexShaderSource2 = GLSL(
	//	layout (location = 0) in vec3 position;
	//	void main()
	//	{
	//	gl_Position = vec4(position.x, position.y, position.z, 1.0);
	//	}
	//);

	//shaderVertexProgram = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(shaderVertexProgram, 1, &vertexShaderSource2, NULL);
	//glCompileShader(shaderVertexProgram);

	///*const GLchar* fragmentShader = GLSL(
	//	out vec4 outColor;
	//void main()
	//{
	//	outColor = vec4(1.0, 0, 0, 1.0);
	//}
	//);*/

	//const GLchar* fragmentShader = GLSL(
	//	out vec4 outColor;
	//	void main()
	//	{
	//	outColor = vec4(gl_FragCoord.x / 800.0, gl_FragCoord.y / 600.0, gl_FragCoord.z / 600.0, 1.0);
	//	}
	//);

	//shaderfragmentProgram = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(shaderfragmentProgram, 1, &fragmentShader, NULL);
	//glCompileShader(shaderfragmentProgram);

	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, shaderVertexProgram);
	//glAttachShader(shaderProgram, shaderfragmentProgram);

	//glBindFragDataLocation(shaderProgram, 0, "outColor");

	//glLinkProgram(shaderProgram);
	//glUseProgram(shaderProgram);

	//GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	//glEnableVertexAttribArray(posAttrib);
	//glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, 0);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
	             vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);

	GLuint indices[] = {
		0, 1, 2, // Triangle 1
		0, 2, 3 // Triangle 2
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
	             indices, GL_STATIC_DRAW);

	const GLchar* vertexShaderSource = GLSL(
		layout(location = 0) in vec3 position;
		layout(location = 1) in vec3 color;
		out vec3 Color;
		void main()
		{
		//interpolate the color of each vertex across the triangle
		Color = color;
		gl_Position = vec4(position.x, position.y, position.z, 1.0);
		gl_PointSize = 10.0;
		}
	);
	shaderVertexProgram = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderVertexProgram, 1, &vertexShaderSource, NULL);
	glCompileShader(shaderVertexProgram);

	const GLchar* fragmentShaderSource = GLSL(
		in vec3 Color;
		out vec4 outColor;
		void main()
		{
		outColor = vec4(Color, 1.0);
		}
	);

	shaderfragmentProgram = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderfragmentProgram, 1, &fragmentShaderSource, NULL);
	glCompileShader(shaderfragmentProgram);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, shaderVertexProgram);
	glAttachShader(shaderProgram, shaderfragmentProgram);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	Scene::display();
}
