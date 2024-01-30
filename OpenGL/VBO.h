#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor (generates a Vertex Buffer Object and links it to vertices)
	VBO(GLfloat* vertices, GLsizeiptr size);

	// Bind the VBO
	void Bind();
	// Unbind the VBO
	void Unbind();
	// Delete the VBO
	void Delete();
};

#endif