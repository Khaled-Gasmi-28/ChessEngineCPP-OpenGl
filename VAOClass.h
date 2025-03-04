#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBOClass.h"

class VAO
{
public:
	GLuint ID;
	VAO();

	void LinkAttri(VBO& VBO, GLuint layout, GLuint numComponenets, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif