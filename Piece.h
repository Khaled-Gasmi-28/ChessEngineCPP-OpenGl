#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderClass.h"
#include "VAOClass.h"
#include "VBOClass.h"
#include "TextureClass.h"

class Piece {
public:
    Piece(int row, int col, const char* texturePath);
    ~Piece();
    void InitPiece();
    Texture texture;  // Texture for the piece
    int row, col;  // Position on the board

    VBO* vbo;
    VAO vao;
private:
    
};

#endif


