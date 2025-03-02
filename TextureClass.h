#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "ShaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum textType, GLenum slot, GLenum format, GLenum pixelType);

	void textUnit(Shader& shader, const char* uniform, GLuint uint);
	void Bind();
	void Unbind();
	void Delete();
};

#endif