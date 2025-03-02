#include "TextureClass.h"

Texture::Texture(const char* image, GLenum textType, GLenum slot, GLenum format, GLenum pixelType) {

	type = textType;
	int WidthImg;
	int heightImg;
	int numColCh;
	unsigned char* bytes = stbi_load(image, &WidthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	Bind();

	glTexParameteri(textType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(textType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(textType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(textType, 0, GL_RGBA, WidthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(textType);

	stbi_image_free(bytes);
	Unbind();
}

void Texture::textUnit(Shader& shader, const char* uniform, GLuint uint) {

	GLuint textureUniform = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1f(textureUniform, uint);
}

void Texture::Bind() {
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}