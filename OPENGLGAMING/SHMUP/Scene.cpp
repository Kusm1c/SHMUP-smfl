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
	std::string texturePath = "img/heights.bmp";
	unsigned int width, height, width2, height2;
	unsigned char* heightMap = BMP::loadBMP_raw(heightMapPath.c_str(), width, height);
	GLuint textureID = BMP::loadBMP_texture(texturePath.c_str(), width2, height2);
	std::cout << width << " " << height << std::endl;
	std::cout << width2 << " " << height2 << std::endl;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLfloat* vertices = new GLfloat[width * height * 8];
	
	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			vertices[(i * height + j) * 8] = (float)i / (float)width;
			vertices[(i * height + j) * 8 + 1] = (float)heightMap[(i * height + j) + 3] / 255.0f * 0.8;
			vertices[(i * height + j) * 8 + 2] = (float)j / (float)height;

			vertices[(i * height + j) * 8 + 3] = 1.0f;
			vertices[(i * height + j) * 8 + 4] = 1.0f;
			vertices[(i * height + j) * 8 + 5] = 1.0f;

			vertices[(i * height + j) * 8 + 6] = (float)i / (float)width2;
			vertices[(i * height + j) * 8 + 7] = (float)j / (float)height2;
		}
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

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, width * height * 8 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (width - 1) * (height - 1) * 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

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
	GLuint shaderVertexProgram;
	shaderVertexProgram = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderVertexProgram, 1, &vertexShaderSource, NULL);
	glCompileShader(shaderVertexProgram);

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
	GLuint shaderfragmentProgram;
	shaderfragmentProgram = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderfragmentProgram, 1, &fragmentShaderSource, NULL);
	glCompileShader(shaderfragmentProgram);


	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, shaderVertexProgram);
	glAttachShader(shaderProgram, shaderfragmentProgram);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)1024 / (float)1024, 0.01f, 1000.0f);
	viewMatrix = glm::lookAt(glm::vec3(0.8f, 1.0f, 2.5f),
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

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(glGetUniformLocation(shaderProgram, "textureSampler"), 0);

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
	glDeleteBuffers(1, &ibo);
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Scene::Update(float dt)
{
	glm::vec3 rotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 rotationAxisY = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 rotationAxisX = glm::vec3(1.0f, 0.0f, 0.0f);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f * dt), rotationAxisX);
	modelMatrix = modelMatrix * scaleMatrix * translationMatrix;
	mvp = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvp"), 1, GL_FALSE, &mvp[0][0]);
	glEnable(GL_DEPTH_TEST);
}

void Scene::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDrawElements(GL_TRIANGLES, 1022 * 1022 * 6, GL_UNSIGNED_INT, 0);
}
