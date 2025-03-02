#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "ShaderClass.h"
#include "VAOClass.h"
#include "VBOClass.h"
#include "EBOClass.h"
#include "Piece.h"

class Board {
public:
    Board();  // Constructor
    ~Board(); // Destructor

    std::vector<float> generateChessboardVertices();
    std::vector<unsigned int> generateChessboardIndices();
    void drawChessboard(Shader& shader);
    void drawPieces(Shader& shader);
    void InitBoard();
    void InitPieces();

private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    int indexCount;
    VAO vao;
    VBO* vbo;
    EBO* ebo;
    Piece* board[8][8];
};

#endif