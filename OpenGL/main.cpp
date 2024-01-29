//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"



const unsigned int width = 800;
const unsigned int height = 800;



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat CubeVertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 5.0f, 0.0f,      1.0f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      1.0f, 0.5f,  0.0f, // Left Side
	-0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      1.0f, 0.5f,  0.0f, // Left Side
	-0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      1.0f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -1.0f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -1.0f, // Non-facing side
	-0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, 0.5f, -1.0f, // Non-facing side
	 0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, 0.5f, -1.0f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      1.0f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      1.0f, 0.5f,  0.0f, // Right side
	 0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      1.0f, 0.5f,  0.0f, // Right side
	 0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      1.0f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  1.0f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  1.0f, // Facing side
	 0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, 0.5f,  1.0f,  // Facing side
	-0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, 0.5f,  1.0f,  // Facing side

	-0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f,  1.0f, 0.0f, // Top side
	-0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f,  1.0f, 0.0f, // Top side
	 0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f,  1.0f, 0.0f, // Top side
	 0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f,  1.0f, 0.0f  // Top side
};

// Indices for vertices order
GLuint CubeIndices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 5, 6, // Left side
	5, 7, 6, // Left side
	8, 9, 10, // Non-facing side
	9, 11, 10, // Non-facing side
	12, 13, 14, // Right side
	13, 14, 15, // Right side
	16, 17, 19, // Facing side
	16, 18, 19, // Facing side
	21, 22, 23, // Top side
	20, 21, 23 // Top side
};

GLfloat planeVertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint PlaneIndices[] =
{
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	Shader shaderProgram2("default.vert", "default.frag");
	Shader shaderProgram3("default.vert", "default.frag");
	Shader shaderProgram4("default.vert", "default.frag");
	Shader shaderProgram5("default.vert", "default.frag");
	Shader shaderProgramRotate("default.vert", "default.frag");
	Shader shaderProgramCube("default.vert", "default.frag");
	Shader shaderProgramCube2("default.vert", "default.frag");
	Shader shaderProgramCube3("default.vert", "default.frag");
	Shader shaderProgramPlane("default.vert", "default.frag");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	VAO VAO2;
	VAO2.Bind();
	VBO VBO2(CubeVertices, sizeof(CubeVertices));
	EBO EBO2(CubeIndices, sizeof(CubeIndices));
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	VAO VAO3;
	VAO3.Bind();
	VBO VBO3(CubeVertices, sizeof(CubeVertices));
	EBO EBO3(CubeIndices, sizeof(CubeIndices));
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();


	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgramRotate.ID, "scale");


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 1.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(2.0f, 0.0f, 2.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	glm::vec3 pyramidPos2 = glm::vec3(2.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel2 = glm::mat4(1.0f);
	pyramidModel2 = glm::translate(pyramidModel2, pyramidPos2);

	glm::vec3 pyramidPos3 = glm::vec3(-2.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel3 = glm::mat4(1.0f);
	pyramidModel3 = glm::translate(pyramidModel3, pyramidPos3);

	glm::vec3 pyramidPos4 = glm::vec3(0.0f, 0.0f, 2.0f);
	glm::mat4 pyramidModel4 = glm::mat4(1.0f);
	pyramidModel4 = glm::translate(pyramidModel4, pyramidPos4);

	glm::vec3 pyramidPos5 = glm::vec3(0.0f, 0.0f, -2.0f);
	glm::mat4 pyramidModel5 = glm::mat4(1.0f);
	pyramidModel5 = glm::translate(pyramidModel5, pyramidPos5);

	glm::vec3 pyramidPos6 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel6 = glm::mat4(1.0f);
	pyramidModel6 = glm::translate(pyramidModel6, pyramidPos6);
	
	glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, -4.0f);
	glm::mat4 cubeModel = glm::mat4(1.0f);
	cubeModel = glm::translate(cubeModel, cubePos);

	glm::vec3 cubePos2 = glm::vec3(2.0f, 0.0f, -2.0f);
	glm::mat4 cubeModel2 = glm::mat4(1.0f);
	cubeModel2 = glm::translate(cubeModel2, cubePos2);

	glm::vec3 cubePos3 = glm::vec3(-2.0f, 0.0f, -2.0f);
	glm::mat4 cubeModel3 = glm::mat4(1.0f);
	cubeModel3 = glm::translate(cubeModel3, cubePos3);

	glm::vec3 planePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 planeModel = glm::mat4(3.0f);
	planeModel = glm::translate(planeModel, planePos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgram2.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram2.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel2));
	glUniform4f(glGetUniformLocation(shaderProgram2.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram2.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgram3.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram3.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel3));
	glUniform4f(glGetUniformLocation(shaderProgram3.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram3.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgram4.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram4.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel4));
	glUniform4f(glGetUniformLocation(shaderProgram4.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram4.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgram5.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram5.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel5));
	glUniform4f(glGetUniformLocation(shaderProgram5.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram5.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgramRotate.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramRotate.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel6));
	glUniform4f(glGetUniformLocation(shaderProgramRotate.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgramRotate.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgramCube.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramCube.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	glUniform4f(glGetUniformLocation(shaderProgramCube.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgramCube.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgramCube2.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramCube2.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel2));
	glUniform4f(glGetUniformLocation(shaderProgramCube2.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgramCube2.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgramCube3.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramCube3.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel3));
	glUniform4f(glGetUniformLocation(shaderProgramCube3.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgramCube3.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	shaderProgramPlane.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramPlane.ID, "model"), 1, GL_FALSE, glm::value_ptr(planeModel));
	glUniform4f(glGetUniformLocation(shaderProgramPlane.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgramPlane.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/
	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string texPath = "/Resources/";

	// Texture
	Texture brickTex((parentDir + texPath + "brick.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	// Original code from the tutorial
	/*Texture brickTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);*/

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Tells OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Exports the camera Position to the Fragment Shader for specular lighting
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		// Export the camMatrix to the Vertex Shader of the pyramid
		camera.Matrix(shaderProgram, "camMatrix");
		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		shaderProgram2.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram2.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram2, "camMatrix");
		brickTex.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		shaderProgram3.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram3.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram3, "camMatrix");
		brickTex.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		shaderProgram4.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram4.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram4, "camMatrix");
		brickTex.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		shaderProgram5.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram5.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram5, "camMatrix");
		brickTex.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		shaderProgramCube.Activate();
		glUniform3f(glGetUniformLocation(shaderProgramCube.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgramCube, "camMatrix");
		brickTex.Bind();
		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(CubeIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		shaderProgramCube2.Activate();
		glUniform3f(glGetUniformLocation(shaderProgramCube2.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgramCube2, "camMatrix");
		brickTex.Bind();
		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(CubeIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		shaderProgramCube3.Activate();
		glUniform3f(glGetUniformLocation(shaderProgramCube3.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgramCube3, "camMatrix");
		brickTex.Bind();
		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(CubeIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		shaderProgramPlane.Activate();
		glUniform3f(glGetUniformLocation(shaderProgramPlane.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgramPlane, "camMatrix");
		brickTex.Bind();
		VAO3.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(PlaneIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		shaderProgramRotate.Activate();
		glUniform3f(glGetUniformLocation(shaderProgramRotate.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgramRotate, "camMatrix");
		brickTex.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Simple timer
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		// Initializes matrices so they are not the null matrix
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		// Assigns different transformations to each matrix
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

		// Outputs the matrices into the Vertex Shader
		int modelLoc = glGetUniformLocation(shaderProgramRotate.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgramRotate.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgramRotate.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Tells OpenGL which Shader Program we want to use
		lightShader.Activate();
		// Export the camMatrix to the Vertex Shader of the light cube
		camera.Matrix(lightShader, "camMatrix");
		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
	VAO3.Delete();
	VBO3.Delete();
	EBO3.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	shaderProgram2.Delete();
	shaderProgram3.Delete();
	shaderProgram4.Delete();
	shaderProgram5.Delete();
	shaderProgramRotate.Delete();
	shaderProgramCube.Delete();
	shaderProgramCube2.Delete();
	shaderProgramCube3.Delete();
	shaderProgramPlane.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}