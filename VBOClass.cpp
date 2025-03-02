#include "VBOClass.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {

	glGenBuffers(1, &ID); // Create VertexBuffer(VBO)
	glBindBuffer(GL_ARRAY_BUFFER, ID);  // bind VBO to current array buffer object
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // Add the vertices array to the buffer
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}