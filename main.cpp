#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

#include "ShaderClass.h"
#include "VAOClass.h"
#include "VBOClass.h"
#include "Board.h"
#include "Global.h"

int main() {

#pragma region Initialise Window

    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Chessboard", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glDisable(GL_DEPTH_TEST);
    stbi_set_flip_vertically_on_load(true);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#pragma endregion

#pragma region Game Loop

    Shader Boardshader("Board.vert", "Board.frag");
    Shader PieceShader("Piece.vert", "Piece.frag");

    Board board;


    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  // Set a light grey background color
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the chessboard
        board.drawChessboard(Boardshader);
        // Draw the pieces
        board.drawPieces(PieceShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

#pragma endregion

#pragma region Destroy Objects

    Boardshader.Delete();
    PieceShader.Delete();
    board.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();

#pragma endregion

    return 0;
}