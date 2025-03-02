#include "Board.h"
#include "Global.h"

Board::Board() {
    InitBoard();
}

Board::~Board() {
    vao.Delete();
    vbo->Delete();
    ebo->Delete();
    delete vbo;
    delete ebo;
}

std::vector<float> Board::generateChessboardVertices() {
    std::vector<float> vertices;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            float x = col * SQUARE_SIZE - 1.0f;
            float y = row * SQUARE_SIZE - 1.0f;

            float color = (row + col) % 2 == 0 ? 0.8f : 0.3f; // Light gray and darker gray

            vertices.insert(vertices.end(), {
                x, y, 0.0f, color, color, color, // Bottom-left
                x + SQUARE_SIZE, y, 0.0f, color, color, color, // Bottom-right
                x + SQUARE_SIZE, y + SQUARE_SIZE, 0.0f, color, color, color, // Top-right
                x, y + SQUARE_SIZE, 0.0f, color, color, color  // Top-left
                });
        }
    }
    return vertices;
}

std::vector<unsigned int> Board::generateChessboardIndices() {
    std::vector<unsigned int> indices;
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        unsigned int offset = i * 4;
        indices.insert(indices.end(), {
            offset, offset + 1, offset + 2,
            offset + 2, offset + 3, offset
            });
    }
    return indices;
}

void Board::InitBoard() {
    // Generate vertices and indices for the chessboard
    vertices = generateChessboardVertices();
    indices = generateChessboardIndices();
    indexCount = indices.size();

    // Initialize VAO and VBO
    vao.Bind();

    vbo = new VBO(vertices.data(), vertices.size() * sizeof(float));
    ebo = new EBO(indices.data(), indices.size() * sizeof(unsigned int));

    vao.LinkAttri(*vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);  // Position
    vao.LinkAttri(*vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Color

    vao.Unbind();
    vbo->Unbind();
    ebo->Unbind();
}

void Board::drawChessboard(Shader& shader) {
    shader.Activate();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}