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
    const static int None = 0;
    const static int King = 1;
    const static int Pawn = 2;
    const static int Knight = 3;
    const static int Queen = 4;
    const static int Bishop = 5;
    const static int Rook = 6;

    const static int White = 8;
    const static int Black = 16;

    Piece(int row, int col, const char* texturePath);
    ~Piece();
    void InitPiece();
    void Delete();
    Texture texture;  // Texture for the piece
    int row, col;  // Position on the board

    VBO* vbo;
    VAO vao;
private:

};

#endif