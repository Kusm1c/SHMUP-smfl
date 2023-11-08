#include "Scene.h"

#include <iostream>
#include <ostream>
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "bmp.h"

Scene::Scene()
{
	std::string heightMapPath = "img/heights.bmp";
	std::string texturePath = "img/map.bmp";
	unsigned int width, height, width2, height2;
	unsigned char* heightMap = BMP::loadBMP_raw(heightMapPath.c_str(), width, height);
	GLuint texture = BMP::loadBMP_texture(texturePath.c_str(), width2, height2);
	std::cout << width << " " << height << std::endl;
	std::cout << width2 << " " << height2 << std::endl;
	GLfloat* vertices = new GLfloat[width * height * 8];
	GLfloat yScale = 64.0f / 1024.0f, yShift = 16.0f;
	for (unsigned int i = 0; i < width * height; i++)
	{
		vertices[i * 8] = (GLfloat)(i % width) / (GLfloat)width;
		vertices[i * 8 + 1] = (GLfloat)heightMap[i * 3] * yScale - yShift;
		vertices[i * 8 + 2] = (GLfloat)(i / width) / (GLfloat)height;
		vertices[i * 8 + 3] = 0.0f;
		vertices[i * 8 + 4] = 1.0f;
		vertices[i * 8 + 5] = 0.0f;
		vertices[i * 8 + 6] = (GLfloat)(i % width) / (GLfloat)width;
		vertices[i * 8 + 7] = (GLfloat)(i / width) / (GLfloat)height;
	}

	GLuint* indices = new GLuint[(width - 1) * (height - 1) * 6];
	for (unsigned int i = 0; i < width - 1; i++)
	{
		for (unsigned int j = 0; j < height - 1; j++)
		{
			indices[(i * (height - 1) + j) * 6] = i * height + j;
			indices[(i * (height - 1) + j) * 6 + 1] = i * height + j + 1;
			indices[(i * (height - 1) + j) * 6 + 2] = (i + 1) * height + j + 1;
			indices[(i * (height - 1) + j) * 6 + 3] = i * height + j;
			indices[(i * (height - 1) + j) * 6 + 4] = (i + 1) * height + j + 1;
			indices[(i * (height - 1) + j) * 6 + 5] = (i + 1) * height + j;
		}
	}
	NUM_STRIPS_REQUIRED = height - 1;
	VERTICES_PER_STRIP = 2 * width;
	const GLchar* vertexShaderSource = GLSL(
		layout(location = 0) in vec3 position;
		layout(location = 1) in vec3 color;
		layout(location = 2) in vec2 uv;
		out vec3 Color;
		out vec2 interpolatedUV;
		uniform mat4 mvp;
		void main()
		{
		gl_Position = mvp * vec4(position, 1.0);
		Color = color;
		interpolatedUV = uv;
		}
	);

	const GLchar* fragmentShaderSource = GLSL(
		in vec3 Color;
		in vec2 interpolatedUV;
		out vec4 outColor;
		uniform sampler2D textureSampler;
		void main()
		{
		outColor = texture(textureSampler, interpolatedUV);
		}
	);
	GLuint shaderVertexProgram;
	GLuint shaderfragmentProgram;
	GLuint shaderProgram;
	shaderVertexProgram = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderVertexProgram, 1, &vertexShaderSource, NULL);
	glCompileShader(shaderVertexProgram);
	shaderfragmentProgram = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderfragmentProgram, 1, &fragmentShaderSource, NULL);
	glCompileShader(shaderfragmentProgram);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, shaderVertexProgram);
	glAttachShader(shaderProgram, shaderfragmentProgram);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER, width * height * 8 * sizeof(GLfloat), vertices,GL_STATIC_DRAW);


	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (width - 1) * (height - 1) * 6 * sizeof(GLuint), indices,GL_STATIC_DRAW);

	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.01f, 100.0f);
	viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::mat4(1.0f);
	mvp = projectionMatrix * viewMatrix * modelMatrix;
	GLuint mvpLoc = glGetUniformLocation(shaderProgram, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvp[0][0]);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteBuffers(1, &vbo);

	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "textureSampler"), 0);
	glActiveTexture(GL_TEXTURE0);

	GLint status;
	char buffer[512];
	glGetShaderiv(shaderVertexProgram, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(shaderVertexProgram, 512, NULL, buffer);
	std::cout << buffer << std::endl;
	glGetShaderiv(shaderfragmentProgram, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(shaderfragmentProgram, 512, NULL, buffer);
	std::cout << buffer << std::endl;
}

Scene::~Scene()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Scene::Update(float dt)
{
}

void Scene::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glBindVertexArray(vao);
	for (unsigned int i = 0; i < NUM_STRIPS_REQUIRED; i++)
	{
		glDrawElements(GL_TRIANGLE_STRIP, VERTICES_PER_STRIP, GL_UNSIGNED_INT,
		               (GLvoid*)(i * VERTICES_PER_STRIP * sizeof(GLuint)));
	}
}
