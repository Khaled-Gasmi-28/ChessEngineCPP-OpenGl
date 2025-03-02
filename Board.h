#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "ShaderClass.h"
#include "VAOClass.h"
#include "VBOClass.h"
#include "EBOClass.h"

class Board {
public:
    Board();  // Constructor
    ~Board(); // Destructor

    std::vector<float> generateChessboardVertices();
    std::vector<unsigned int> generateChessboardIndices();
    void drawChessboard(Shader& shader);
    void InitBoard();

private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    int indexCount;
    VAO vao;
    VBO* vbo;
    EBO* ebo;
};

#endif