#include "Skybox.h"

#include <iostream>
#include <string>

#include "bmp.h"


Skybox::Skybox(Camera camera)
{
	//make a cube
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat vertices[] = {
		// Front face
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		// Back face
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		// Right face
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,

		// Left face
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,

		// Top face
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,

		// Bottom face
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	const char* vsSource = GLSL(
		layout (location = 0) in vec3 position;
		out vec3 interpolatedUV;
		uniform mat4 model;
		uniform mat4 projection;
		uniform mat4 view;
		void main()
		{
			interpolatedUV = position;
			gl_Position = projection * view * model * vec4(position, 1.0);
		}
	);

	vertexShaderProgram = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderProgram, 1, &vsSource, NULL);
	glCompileShader(vertexShaderProgram);

	const char* fsSource = GLSL(
		in vec3 interpolatedUV;

		out vec4 FragColor;

		uniform samplerCube skybox;

		void main()
		{
			FragColor = texture(skybox, interpolatedUV);
		}
	);

	fragmentShaderProgram = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderProgram, 1, &fsSource, NULL);
	glCompileShader(fragmentShaderProgram);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f));
	projectionMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	modelMatrix = glm::mat4(1.0f) * scaleMatrix;
	projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projection");
	viewMatrixLocation = glGetUniformLocation(shaderProgram, "view");
	modelMatrixLocation = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (int i = 0; i < 6; i++)
	{
		std::string filename = "img/sky_";
		filename += std::to_string(i);
		filename += ".bmp";
		std::cout << filename << std::endl;
		GLuint width, height;
		unsigned char* data = BMP::loadBMP_raw(filename.c_str(), width, height);
		if (data == 0)
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		else
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	viewMatrix = glm::mat4(glm::mat3(camera.GetViewMatrix()));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	GLint status;
	char buffer[512];
	glGetShaderiv(vertexShaderProgram, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(vertexShaderProgram, 512, NULL, buffer);
	std::cout << status << " " << buffer << std::endl;
	glGetShaderiv(fragmentShaderProgram, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(fragmentShaderProgram, 512, NULL, buffer);
	std::cout << status << " " << buffer << std::endl;
}

Skybox::~Skybox()
{
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao);
}

void Skybox::Update(float dt)
{
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Skybox::display()
{
	glDepthMask(GL_FALSE);
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE);
}
