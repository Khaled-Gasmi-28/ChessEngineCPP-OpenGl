#include "Board.h"
#include "Global.h"

// Initialize the static member outside the class
const std::unordered_map<char, int> Piece::PieceTypeFromSymbol = {
    {'k', Piece::King}, {'p', Piece::Pawn}, {'n', Piece::Knight},
    {'b', Piece::Bishop}, {'r', Piece::Rook}, {'q', Piece::Queen}
};

Board::Board() {
    InitPieces(START_FEN);
    InitBoard();
}

Board::~Board() {
    vao.Delete();
    vbo->Delete();
    ebo->Delete();
    delete vbo;
    delete ebo;

    // Clean up dynamically allocated pieces
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] != nullptr) {
                delete board[i][j];
            }
        }
    }
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

void Board::InitPieces(std::string FEN_String) {
    // Initialize pieces on the board. This is where you can place your pieces.

    //initialse square array 
    int file = 0;
    int rank = 7;

    for (char c : FEN_String)
    {
        if (c == '/') {
            file = 0;
            rank--;
        }
        else {
            if (std::isdigit(c)) { 
                file += c - '0';  
            }
            else {
                int PieceColor = std::isupper(c) ? Piece::White : Piece::Black;
                int PieceType = Piece::PieceTypeFromSymbol.at(std::tolower(c));
                Square[rank * 8 + file] = PieceType | PieceColor;
                file++;
            }
        }
    }

    //set up the Board for drawing
    rank = 0;
    file = 0;

    for (int i = 0;i < 64;i++) {
        /*
        if (i % 8 == 0) {
            std::cout << std::endl;
        }
        std::cout << Square[i] << " || ";
        */

        rank = i / 8;
        file = i % 8;
        if (Square[i] == 0) continue;
        else board[rank][file] = ConvertIntToPiece(Square[i], rank, file);
        
    }
}

Piece* Board::ConvertIntToPiece(int SquareValue, int rank, int file) {
    std::string TexturePath = "Textures/";

    switch (SquareValue) {
    case 9:  TexturePath += "King_Black"; break;
    case 10: TexturePath += "Pawn_Black"; break;
    case 11: TexturePath += "Knight_Black"; break;
    case 12: TexturePath += "Queen_Black"; break;
    case 13: TexturePath += "Bishop_Black"; break;
    case 14: TexturePath += "Rook_Black"; break;
    case 17: TexturePath += "King_White"; break;
    case 18: TexturePath += "Pawn_White"; break;
    case 19: TexturePath += "Knight_White"; break;
    case 20: TexturePath += "Queen_White"; break;
    case 21: TexturePath += "Bishop_White"; break;
    case 22: TexturePath += "Rook_White"; break;
    default: return nullptr; // Return nullptr if SquareValue is invalid
    }

    TexturePath += ".png";

    return new Piece(rank, file, TexturePath.c_str());
}

void Board::drawChessboard(Shader& shader) {
    shader.Activate();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    vao.Unbind();
}

void Board::drawPieces(Shader& shader) {
    shader.Activate();
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] != nullptr) {
                board[i][j]->InitPiece();
                board[i][j]->texture.Bind();
                board[i][j]->vao.Bind();
                glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
                board[i][j]->vao.Unbind();
                board[i][j]->texture.Unbind();
            }
        }
    }
}

void Board::Delete() {

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] != nullptr) {
                board[i][j]->Delete();
            }
        }
    }

    vao.Delete();
    vbo->Delete();
    ebo->Delete();
}