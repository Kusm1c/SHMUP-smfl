#include "Triangle2D.h"

#include <iostream>
#include <ostream>
#include <vcruntime.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "bmp.h"

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

	GLfloat vertices[] = {
		// Front face
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,

		// Back face
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,

		// Right face
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,

		// Left face
		-0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 0.0f,	0.0f, 0.0f,

		// Top face
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 1.0f,	0.0f, 0.0f,

		// Bottom face
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0, // Front face

		4, 5, 6,
		6, 7, 4, // Back face

		8, 9, 10,
		10, 11, 8, // Right face

		12, 13, 14,
		14, 15, 12, // Left face

		16, 17, 18,
		18, 19, 16, // Top face

		20, 21, 22,
		22, 23, 20 // Bottom face
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
	             vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);

	//GLuint indices[] = {
	//	0, 1, 2, // Triangle 1
	//	0, 2, 3 // Triangle 2
	//};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
	             indices, GL_STATIC_DRAW);
	
	const GLchar* vertexShaderSource = GLSL(
		layout(location = 0) in vec3 position;
		layout(location = 1) in vec3 color;
		layout(location = 2) in vec2 UV;
		out vec3 Color;
		out vec2 interpolatedUV;
		uniform mat4 mvp;
		void main()
		{
		//interpolate the color of each vertex across the triangle
			Color = color;
		//gl_Position = vec4(position.x, position.y, position.z, 1.0);
			gl_Position = mvp * vec4(position, 1.0);
			interpolatedUV = UV;
		}
	);
	shaderVertexProgram = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderVertexProgram, 1, &vertexShaderSource, NULL);
	glCompileShader(shaderVertexProgram);

	/*const GLchar* fragmentShaderSource = GLSL(
		in vec3 Color;
		out vec4 outColor;
		void main()
		{
		outColor = vec4(Color, 1.0);
		}
	);*/

	const GLchar* fragmentShaderFromTextBmp = GLSL(
		in vec3 Color;
		in vec2 interpolatedUV;
		out vec4 outColor;
		uniform sampler2D tex;
		void main()
		{
		vec4 texel = texture(tex, interpolatedUV);
		outColor = texel /** vec4(Color, 1.0)*/;
		}
	);

	shaderfragmentProgram = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderfragmentProgram, 1, &fragmentShaderFromTextBmp, NULL);
	glCompileShader(shaderfragmentProgram);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, shaderVertexProgram);
	glAttachShader(shaderProgram, shaderfragmentProgram);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.01f, 100.0f);
	viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::mat4(1.0f);
	mvp = projectionMatrix * viewMatrix * modelMatrix;
	GLuint mvpLoc = glGetUniformLocation(shaderProgram, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<void*>(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	unsigned int width, height;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	textureID = BMP::loadBMP_texture("img/test.bmp", width, height);
	glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);
	std::cout << width << " " << height << std::endl;
	GLint status;
	char buffer[512];
	glGetShaderiv(shaderVertexProgram, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(shaderVertexProgram, 512, NULL, buffer);
	std::cout << buffer << std::endl;
	glGetShaderiv(shaderfragmentProgram, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(shaderfragmentProgram, 512, NULL, buffer);
	std::cout << buffer << std::endl;
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
	glm::vec3 rotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 rotationAxisY = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 rotationAxisX = glm::vec3(1.0f, 0.0f, 0.0f);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f * dt), rotationAxisX+rotationAxisY);
	modelMatrix = modelMatrix * scaleMatrix * translationMatrix;
	mvp = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvp"), 1, GL_FALSE, &mvp[0][0]);
	glEnable(GL_DEPTH_TEST);
}

void Triangle2D::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	Scene::display();
}