#include "Board.h"
#include "Global.h"

Board::Board() {
    InitBoard();
    InitPieces();
}

Board::~Board() {

    // Clean up dynamically allocated pieces
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j]->~Piece();  // Delete each piece when done
        }
    }

    vao.Delete();
    vbo->Delete();
    glDeleteBuffers(1, &EBO);
    delete vbo;
}

std::vector<float> Board::generateChessboardVertices() {
    std::vector<float> vertices;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            float x = col * SQUARE_SIZE - 1.0f;
            float y = row * SQUARE_SIZE - 1.0f;

            float color = (row + col) % 2 == 0 ? 0.8f : 0.3f; // Light gray and lighter black

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
    // Initialize the board matrix to null (no pieces)
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = nullptr;  // No piece in the square
        }
    }

    // Now initialize the pieces
    InitPieces();
}

void Board::drawChessboard(Shader& shader) {
    shader.Activate();

    // Loop through all the board positions
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            bool hasPiece = (board[row][col] != nullptr);  // Check if there's a piece

            // Set the "hasPiece" uniform (1 if there's a piece, 0 if not)
            glUniform1i(glGetUniformLocation(shader.ID, "hasPiece"), hasPiece);

            if (hasPiece) {
                // Draw piece using texture if present
                Piece* piece = board[row][col];
                piece->texture.Bind();  // Bind the texture for the piece
                glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
                piece->texture.Unbind();  // Unbind the texture after drawing
            }
            else {
                // If no piece, draw an empty square with alternating colors
                float color = (row + col) % 2 == 0 ? 0.8f : 0.3f;  // Light gray and darker gray
                glUniform3f(glGetUniformLocation(shader.ID, "Color"), color, color, color);
                glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);  // Empty square
            }
        }
    }

    vao.Unbind();
}

void Board::InitPieces() {
    // Initialize pieces on the board. This is where you can place your pieces.
    // For simplicity, assuming we have two rooks for this example.
    board[0][0] = new Piece(0, 0, "rook_white.png");
    board[0][7] = new Piece(0, 7, "rook_white.png");
    board[7][0] = new Piece(7, 0, "rook_white.png");
    board[7][7] = new Piece(7, 7, "rook_white.png");

    // Initialize other pieces (pawns, knights, etc.) similarly...
}