#include "Triangle2D.h"

#include <vcruntime.h>

#define GLSL(shader) "#version 330 core\n" #shader

Triangle2D::Triangle2D() : Scene()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLfloat vertices[] = {
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0, // Vertex 1 (X, Y, Z, R, G, B)
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0, // Vertex 2 (X, Y, Z, R, G, B)
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0, // Vertex 3 (X, Y, Z, R, G, B)

		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0, // Vertex 1 (X, Y, Z, R, G, B)
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0, // Vertex 3 (X, Y, Z, R, G, B)
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0, // Vertex 4 (X, Y, Z, R, G, B)
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
// #include <SFML/Graphics.hpp>
// #include <SFML/OpenGL.hpp>
//
// int main() {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "Spinning Cube");
//     window.setVerticalSyncEnabled(true);
//
//     // Initialize OpenGL
//     glEnable(GL_DEPTH_TEST);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(45.f, 1.f, 1.f, 500.f);
//     glMatrixMode(GL_MODELVIEW);
//
//     // Main loop
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//         }
//
//         // Clear the depth buffer and window
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//         // Set up the camera position and orientation
//         glLoadIdentity();
//         glTranslatef(0.f, 0.f, -200.f);
//         glRotatef(sf::Clock().getElapsedTime().asSeconds() * 50, 1.f, 0.f, 0.f);
//         glRotatef(sf::Clock().getElapsedTime().asSeconds() * 30, 0.f, 1.f, 0.f);
//
//         // Draw the spinning cube
//         glBegin(GL_QUADS);
//         // Front face
//         glColor3f(1.f, 0.f, 0.f);
//         glVertex3f(-50.f, -50.f, 50.f);
//         glVertex3f(50.f, -50.f, 50.f);
//         glVertex3f(50.f, 50.f, 50.f);
//         glVertex3f(-50.f, 50.f, 50.f);
//         // Back face
//         glColor3f(0.f, 1.f, 0.f);
//         glVertex3f(-50.f, -50.f, -50.f);
//         glVertex3f(50.f, -50.f, -50.f);
//         glVertex3f(50.f, 50.f, -50.f);
//         glVertex3f(-50.f, 50.f, -50.f);
//         // Left face
//         glColor3f(0.f, 0.f, 1.f);
//         glVertex3f(-50.f, -50.f, 50.f);
//         glVertex3f(-50.f, -50.f, -50.f);
//         glVertex3f(-50.f, 50.f, -50.f);
//         glVertex3f(-50.f, 50.f, 50.f);
//         // Right face
//         glColor3f(1.f, 1.f, 0.f);
//         glVertex3f(50.f, -50.f, 50.f);
//         glVertex3f(50.f, -50.f, -50.f);
//         glVertex3f(50.f, 50.f, -50.f);
//         glVertex3f(50.f, 50.f, 50.f);
//         // Top face
//         glColor3f(0.f, 1.f, 1.f);
//         glVertex3f(-50.f, 50.f, 50.f);
//         glVertex3f(50.f, 50.f, 50.f);
//         glVertex3f(50.f, 50.f, -50.f);
//         glVertex3f(-50.f, 50.f, -50.f);
//         // Bottom face
//         glColor3f(1.f, 0.f, 1.f);
//         glVertex3f(-50.f, -50.f, 50.f);
//         glVertex3f(50.f, -50.f, 50.f);
//         glVertex3f(50.f, -50.f, -50.f);
//         glVertex3f(-50.f, -50.f, -50.f);
//         glEnd();
//
//         // End the current frame
//         window.display();
//     }
//
//     return 0;
// }
// #include <SFML/Graphics.hpp>
// #include <SFML/OpenGL.hpp>
//
// const GLchar* vertexShaderSource = R"GLSL(
//     layout(location = 0) in vec3 position;
//     layout(location = 1) in vec3 color;
//     out vec3 Color;
//     uniform mat4 model;
//     uniform mat4 view;
//     uniform mat4 projection;
//     void main()
//     {
//         // interpolate the color of each vertex across the cube
//         Color = color;
//         gl_Position = projection * view * model * vec4(position, 1.0);
//     }
// )GLSL";
//
// const GLchar* fragmentShaderSource = R"GLSL(
//     in vec3 Color;
//     out vec4 outColor;
//     void main()
//     {
//         outColor = vec4(Color, 1.0);
//     }
// )GLSL";
//
// int main() {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "Spinning Cube");
//     window.setVerticalSyncEnabled(true);
//
//     // Initialize OpenGL
//     glEnable(GL_DEPTH_TEST);
//     glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
//
//     // Create and compile shaders
//     GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//     glCompileShader(vertexShader);
//
//     GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//     glCompileShader(fragmentShader);
//
//     // Link shaders and create shader program
//     GLuint shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
//     glUseProgram(shaderProgram);
//
//     // Vertex data
//     GLfloat vertices[] = {
//         // Front face
//         -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
//         0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
//         0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
//         -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
//         // ... (define other faces similarly)
//     };
//
//     GLuint indices[] = {
//         0, 1, 2, 2, 3, 0,
//         // ... (define other indices for the remaining faces)
//     };
//
//     GLuint vao, vbo, ibo;
//     glGenVertexArrays(1, &vao);
//     glBindVertexArray(vao);
//
//     glGenBuffers(1, &vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//     glGenBuffers(1, &ibo);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//     // Specify vertex attributes
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//     glEnableVertexAttribArray(1);
//
//     // Main loop
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//         }
//
//         // Clear the buffer
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//         // Set up transformations
//         glm::mat4 model, view, projection;
//         model = glm::rotate(model, glm::radians(static_cast<float>(SFML::Clock().getElapsedTime().asSeconds() * 50)), glm::vec3(1.0f, 0.0f, 0.0f));
//         model = glm::rotate(model, glm::radians(static_cast<float>(SFML::Clock().getElapsedTime().asSeconds() * 30)), glm::vec3(0.0f, 1.0f, 0.0f));
//         view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//         projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
//
//         // Get the uniform locations and set the matrices
//         GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
//         glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//         GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
//         glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//         GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
//         glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//         // Draw the cube
//         glBindVertexArray(vao);
//         glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//         glBindVertexArray(0);
//
//         // End the current frame
//         window.display();
//     }
//
//     // Cleanup
//     glDeleteVertexArrays(1, &vao);
//     glDeleteBuffers(1, &vbo);
//     glDeleteBuffers(1, &ibo);
//
//     // Delete shaders and program
//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);
//     glDeleteProgram(shaderProgram);
//
//     return 0;
// }
// Vertex data for a complete cube
// GLfloat vertices[] = {
// 	// Front face
// 	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
// 	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
// 	0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
// 	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
//
// 	// Back face
// 	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
// 	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
// 	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
// 	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
//
// 	// Right face
// 	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
// 	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
// 	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
// 	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
//
// 	// Left face
// 	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
// 	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
// 	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
// 	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
//
// 	// Top face
// 	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
// 	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
// 	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
// 	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
//
// 	// Bottom face
// 	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
// 	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,
// 	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
// 	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f
// };
//
// GLuint indices[] = {
// 	0, 1, 2, 2, 3, 0,    // Front face
// 	4, 5, 6, 6, 7, 4,    // Back face
// 	8, 9, 10, 10, 11, 8,  // Right face
// 	12, 13, 14, 14, 15, 12, // Left face
// 	16, 17, 18, 18, 19, 16, // Top face
// 	20, 21, 22, 22, 23, 20  // Bottom face
// };
