#include <stdlib.h>
#include "include/GLFW/glfw3.h"

int main()
{
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello, World!", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glPointSize(3);
        glBegin(GL_POINTS);
        glVertex3f(0, 0, 0);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

