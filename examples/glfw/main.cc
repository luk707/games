#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"

#include "common/gl/index_buffer.hh"
#include "common/gl/parse_shader.hh"
#include "common/gl/renderer.hh"
#include "common/gl/shader.hh"
#include "common/gl/vertex_array.hh"
#include "common/gl/vertex_buffer.hh"
#include "common/gl/vertex_buffer_layout.hh"

int main()
{
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello, World!", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        exit(EXIT_FAILURE);

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        // Load shader
        std::ifstream stream("common/gl/shaders/basic.glsl");

        if (!stream)
        {
            std::cout << "Cannot open file!" << std::endl;
            exit(EXIT_FAILURE);
        }

        Common::GL::ShaderSource shaderSource = Common::GL::ParseShader(stream);
        Common::GL::Shader shader(shaderSource);

        // Setup vertex array, vertex buffer and index buffer
        float positions[] = {
            -0.5f,  0.5f,
            0.5f,  0.5f,
            -0.5f, -0.5f,
            0.5f, -0.5f
        };
        unsigned int indicies[] = {
            2, 3, 1,
            2, 1, 0
        };
        Common::GL::VertexArray va;
        Common::GL::VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        Common::GL::VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        Common::GL::IndexBuffer ib(indicies, 6);

        float r = 0.0f;
        float increment = 0.05f;

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            
            // Render geometery
            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            va.Bind();
            ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

