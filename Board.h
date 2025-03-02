#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Piece.h"
#include "ShaderClass.h"
#include "VAOClass.h"

class Board {
public:
    Board();  // Constructor
    ~Board(); // Destructor

    std::vector<float> generateChessboardVertices();
    std::vector<unsigned int> generateChessboardIndices();
    void drawChessboard(Shader& shader);
    void InitBoard();
    void InitPieces();  // Initialize pieces on the board
    void DrawPieces(Shader& shader);  // Draw pieces

private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    int indexCount;
    VAO vao;
    VBO* vbo;
    GLuint EBO;
    Piece* board[8][8];
};

#endif