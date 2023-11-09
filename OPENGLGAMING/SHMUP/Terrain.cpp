#include "Terrain.h"
#include "Scene.h"

#include <iostream>
#include <ostream>
#include <string>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <SFML/Window/Mouse.hpp>

#include "bmp.h"

Terrain::Terrain()
{
	std::string heightMapPath = "img/heights.bmp";
	std::string texturePath = "img/map.bmp";
	unsigned char* heightMap = BMP::loadBMP_raw(heightMapPath.c_str(), width, height);
	textureID = BMP::loadBMP_texture(texturePath.c_str(), width2, height2);
	std::cout << width << " " << height << std::endl;
	std::cout << width2 << " " << height2 << std::endl;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	vertices = new GLfloat[width * height * 8];
	
	for (unsigned int i = 0; i < width; i++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			vertices[(j * width + (width - i - 1)) * 8] = (float)j / (float)height + 0.05;
			vertices[(j * width + (width - i - 1)) * 8 + 1] = (float)heightMap[(i * height + j) * 3] / 255.0f * 0.2;
			vertices[(j * width + (width - i - 1)) * 8 + 2] = (float)i / (float)width + 0.05;

			vertices[(j * width + (width - i - 1)) * 8 + 3] = 1.0f;
			vertices[(j * width + (width - i - 1)) * 8 + 4] = 1.0f;
			vertices[(j * width + (width - i - 1)) * 8 + 5] = 1.0f;

			vertices[(j * width + (width - i - 1)) * 8 + 6] = (float)j / (float)height2;
			vertices[(j * width + (width - i - 1)) * 8 + 7] = (float)i / (float)width2;
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
			Color = color;
			gl_Position = mvp * vec4(position, 1.0);
			interpolatedUV = uv;
		}
	);
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

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
	
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)1024 / (float)1024, 0.01f, 1000.0f);
	viewMatrix = glm::lookAt(glm::vec3(0.8f, 2.0f, 2.5f),  // Camera position (x, y, z)
							 glm::vec3(0.0f, 0.0f, 0.0f),  // Look-at position (x, y, z) - center of the plane
							 glm::vec3(0.0f, 1.0f, -1.0f)); // Up vector (x, y, z) - pointing upwards
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
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
	std::cout << buffer << std::endl;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
	std::cout << buffer << std::endl;
}

Terrain::~Terrain()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Terrain::Update(float dt)
{
	Scene::Update(dt);
	glm::vec3 rotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 rotationAxisY = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 rotationAxisX = glm::vec3(1.0f, 0.0f, 0.0f);
	// rotationMatrix = glm::rotate(modelMatrix, glm::radians(45.0f * dt), rotationAxisX);
	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	mvp = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvp"), 1, GL_FALSE, &mvp[0][0]);
	/*glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUseProgram(shaderProgram);
	glEnable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(shaderProgram, "textureSampler"), 0);*/
}

void Terrain::display()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawElements(GL_TRIANGLES, 1022 * 1022 * 6, GL_UNSIGNED_INT, 0);
}