//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include "ShaderClass.h"
#include "VAOClass.h"
#include "VBOClass.h"
#include <vector>
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
#pragma endregion

    Shader shader("default.vert", "default.frag");

    Board board;

#pragma region Game Loop

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  // Set a light grey background color
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the chessboard (with pieces or empty squares)
        board.drawChessboard(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

#pragma endregion


#pragma region Destroy Objects

    //board.~Board();
    glfwDestroyWindow(window);
    glfwTerminate();

#pragma endregion

    return 0;
}
