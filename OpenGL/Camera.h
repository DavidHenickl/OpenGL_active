#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
public:
	// Main vectors
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// Prevent the camera from jumping around when first clicking left click
	bool firstClick = true;

	// width and height of the window
	int width;
	int height;

	// camera speed and sensitivity when looking around
	float speed = 0.1f;
	float sensitivity = 100.0f;

	// Constructor
	Camera(int width, int height, glm::vec3 position);

	// Update the camera matrix to the Vertex Shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Export the camera matrix to a shader
	void Matrix(Shader& shader, const char* uniform);
	// Handle camera inputs
	void Inputs(GLFWwindow* window);
};
#endif