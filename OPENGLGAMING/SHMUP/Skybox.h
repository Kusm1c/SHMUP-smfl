#pragma once

#include <GL/glew.h>

#include <vcruntime.h>

#include <glm/fwd.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Camera.h"


#define GLSL(shader) "#version 330 core\n" #shader

#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A



class Skybox
{
public:
	Skybox(Camera camera);
	~Skybox();

	void Update();
	void display();

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	glm::mat4 scaleMatrix = glm::mat4(1.0f);

private:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

    GLuint vertexShaderProgram;
    GLuint fragmentShaderProgram;
    GLuint shaderProgram;

	GLuint modelMatrixLocation;
	GLuint viewMatrixLocation;
	GLuint projectionMatrixLocation;

	GLuint textureID;
};

