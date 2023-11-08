#pragma once
#include <glm/mat4x4.hpp>
#include "Scene.h"

class Terrain : public Scene
{
public:
    Terrain();
    ~Terrain();
    void Update(float dt);
    void display();
    float getHeightOfGroundAtPosition(float x, float z) const;
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 translationMatrix = glm::mat4(1.0f);
    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    glm::mat4 scaleMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::mat4(1.0f);

private:
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLint positionAttrib;
    GLfloat* vertices;
    unsigned int width, height, width2, height2;
    unsigned int textureID;
	
    glm::mat4 mvp = glm::mat4(1.0f);
};
