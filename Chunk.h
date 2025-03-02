#ifndef CHUNK_H
#define CHUNK_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderClass.h"
#include "Camera.h"
#include "Global.h"
using namespace glm;

const int X_SIZE = 32;
const int Y_SIZE = 32;
const int Z_SIZE = 32;

class Chunk
{
	Block blocks[X_SIZE*Y_SIZE*Z_SIZE];
public:
	Chunk();
	void InitChunk();
	void DrawChunk(Shader& shader, Camera& camera);
};

#endif


