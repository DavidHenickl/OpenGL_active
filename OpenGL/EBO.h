#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor (generates a Elements Buffer Object and links it to indices)
	EBO(GLuint* indices, GLsizeiptr size);

	// Bind the EBO
	void Bind();
	// Unbind the EBO
	void Unbind();
	// Delete the EBO
	void Delete();
};

#endif