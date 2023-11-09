#include "MiniMap.h"

MiniMap::MiniMap()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat vertices[] = {
		//make a square (2 triangles)
		-0.5f, 0.5f, 0.0f, // Vertex 1 (X, Y, Z)
		0.5f, 0.5f, 0.0f, // Vertex 2 (X, Y, Z)
		0.5f, -0.5f, 0.0f, // Vertex 3 (X, Y, Z)

		0.5f, -0.5f, 0.0f, // Vertex 3 (X, Y, Z)
		0.5f, 0.5f, 0.0f, // Vertex 4 (X, Y, Z)
		0.5f, -0.5f, 0.0f, // Vertex 1 (X, Y, Z)
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
	             vertices, GL_STATIC_DRAW);

	GLuint indices[] = {
		0, 1, 2, // Triangle 1
		3, 4, 5 // Triangle 2
	};

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
	             indices, GL_STATIC_DRAW);

	std::string texturePath = "img/map.bmp";
	textureID = BMP::loadBMP_texture(texturePath.c_str(), width, height);

	const GLchar* vertexShaderMiniMap = GLSL(
		layout(location = 0) in vec3 position;
		layout(location = 1) in vec2 uv;
		out vec2 UV;
		uniform mat4 mvp;
		void main()
		{
		gl_Position = mvp * vec4(position, 1.0);
		UV = uv;
		}
	);

	vertexShaderProgram = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderProgram, 1, &vertexShaderMiniMap, NULL);
	glCompileShader(vertexShaderProgram);

	const GLchar* fragmentShaderMiniMap = GLSL(
		in vec2 UV;
		out vec4 outColor;
		uniform sampler2D textureSampler;
		void main()
		{
		outColor = texture(textureSampler, UV);
		}
	);

	fragmentShaderProgram = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderProgram, 1, &fragmentShaderMiniMap, NULL);
	glCompileShader(fragmentShaderProgram);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glUniform1i(glGetUniformLocation(shaderProgram, "textureSampler"), 0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f));
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.75f, 0.75f, 0.0f));
	glm::mat4 modelMatrix = translationMatrix * scaleMatrix;
	glm::mat4 projectionMatrix = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);
	glm::mat4 mvp = projectionMatrix * modelMatrix;

	GLint status;
	char buffer[512];
	glGetShaderiv(vertexShaderProgram, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(vertexShaderProgram, 512, NULL, buffer);
	std::cout << buffer << std::endl;
	glGetShaderiv(fragmentShaderProgram, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(fragmentShaderProgram, 512, NULL, buffer);
	std::cout << buffer << std::endl;
}

MiniMap::~MiniMap()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao);
	glDeleteTextures(1, &textureID);
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShaderProgram);
	glDeleteShader(vertexShaderProgram);
}

void MiniMap::Update(float dt)
{
	Scene::Update(dt);
}

void MiniMap::display()
{
	Scene::display();
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
}
