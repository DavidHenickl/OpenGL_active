#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// Assign a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Bind a texture
	void Bind();
	// Unbind a texture
	void Unbind();
	// Delete a texture
	void Delete();
};
#endif