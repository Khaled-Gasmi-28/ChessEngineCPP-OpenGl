#include "Piece.h"

Piece::Piece(int row, int col, const char* texturePath)
    : row(row), col(col), texture(texturePath, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE) {

    InitPiece();
}

Piece::~Piece() {
    // Check if vbo is initialized before deleting
    if (vbo != nullptr) {
        vao.Delete();
        vbo->Delete();
        delete vbo;
    }
}

void Piece::InitPiece() {
    float offset = 0.25f;
    // Calculate position based on the square it belongs to
    float x = col * 0.25f - 1.0f;  // Adjust to grid coordinates
    float y = row * 0.25f - 1.0f;  // Adjust to grid coordinates

    // Define square vertices for the piece (with texture coordinates)
    std::vector<float> pieceVertices = {
        x, y, 0.0f, 0.0f, 0.0f,  // Bottom-left
        x + offset, y, 0.0f, 1.0f, 0.0f, // Bottom-right
        x + offset, y + offset, 0.0f, 1.0f, 1.0f, // Top-right
        x, y + offset, 0.0f, 0.0f, 1.0f  // Top-left
    };

    // Initialize VBO if not already initialized
    if (vbo == nullptr) {
        vbo = new VBO(pieceVertices.data(), pieceVertices.size() * sizeof(float));
    }

    vao.Bind();
    vao.LinkAttri(*vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);  // Position
    vao.LinkAttri(*vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Texture coords
    vao.Unbind();
}

void Piece::Delete() {

    texture.Delete();
    vbo->Delete();
    vao.Delete();

}