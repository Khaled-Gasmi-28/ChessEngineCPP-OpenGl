#include "Chunk.h"


Chunk::Chunk() {
	InitChunk();
}

void Chunk::InitChunk() {

	for (int x = 0; x < X_SIZE; x++) {
		for (int y = 0;y < Y_SIZE; y++) {
			for (int z = 0; z < Z_SIZE; z++) {
				//blocks[x][y][z] = true;
                int index = x + y * X_SIZE + z * X_SIZE * Y_SIZE;
				blocks[index].visible = true;
				blocks[index].x = x;
				blocks[index].y = y;
				blocks[index].z = z;
				
				
			}
		}
	}
}

void Chunk::DrawChunk(Shader& shader, Camera& camera) {
    for (int x = 0; x < X_SIZE; x++) {
        for (int y = 0; y < Y_SIZE; y++) {
            for (int z = 0; z < Z_SIZE; z++) {
                // Calculate the 1D index from the 3D coordinates (x, y, z)
                int index = x + y * X_SIZE + z * X_SIZE * Y_SIZE;
                Block& block = blocks[index];

                // Skip rendering if the block is not visible
                if (!block.visible) { continue; }

                glm::vec3 blockPosition = glm::vec3(x, y, z);
                if (!camera.IsBlockInFrustum(blockPosition, 0.5f)) { continue; }

                mat4 model = mat4(1.0f);
                model = translate(model, vec3(x, y, z)); // Translate block to the correct position
                glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

                // Render only if there isn't a block next to it
                if (x == 0 || !blocks[(x - 1) + y * X_SIZE + z * X_SIZE * Y_SIZE].visible) { glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(GLuint))); } // Left Face
                if (x == X_SIZE - 1 || !blocks[(x + 1) + y * X_SIZE + z * X_SIZE * Y_SIZE].visible){ glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(GLuint))); }// Right Face
                if (y == 0 || !blocks[x + (y - 1) * X_SIZE + z * X_SIZE * Y_SIZE].visible) { glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(GLuint))); }// Bottom Face
                if (y == Y_SIZE - 1 || !blocks[x + (y + 1) * X_SIZE + z * X_SIZE * Y_SIZE].visible){ glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(GLuint))); }// Top Face
                if (z == 0 || !blocks[x + y * X_SIZE + (z - 1) * X_SIZE * Y_SIZE].visible){ glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint))); }// Front Face
                if (z == Z_SIZE - 1 || !blocks[x + y * X_SIZE + (z + 1) * X_SIZE * Y_SIZE].visible){ glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0)); }// Back Face
            }
        }
    }
}
