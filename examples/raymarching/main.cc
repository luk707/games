#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/scalar_constants.hpp>

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

    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Hello, World!", NULL, NULL);

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
        std::ifstream stream("examples/shader_playground/uv.glsl");

        if (!stream)
        {
            std::cout << "Cannot open file!" << std::endl;
            exit(EXIT_FAILURE);
        }

        Common::GL::ShaderSource shaderSource = Common::GL::ParseShader(stream);
        Common::GL::Shader shader(shaderSource);

        // Setup vertex array, vertex buffer and index buffer
        float verticies[] = {
            -1.0f, -1.0f,
            1.0f, -1.0f,
            1.0f, 1.0f,
            -1.0f, 1.0f
        };
        unsigned int indicies[] = {
            0, 1, 2,
            0, 2, 3
            
        };
        Common::GL::VertexArray va;
        Common::GL::VertexBuffer vb(verticies, 8 * sizeof(float));
        Common::GL::VertexBufferLayout layout;
        layout.Push<float>(2); // XY
        va.AddBuffer(vb, layout);
        Common::GL::IndexBuffer ib(indicies, 3 * 2);

        glEnable(GL_MULTISAMPLE);

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.4f, 0.6f, 0.9f, 1.0f);

            
            // Render geometery
            shader.Bind();
            // X: Time
            // Y: Aspect
            // Z: resx
            // W: resy
            shader.SetUniform4f("u_Data", glfwGetTime(),  16.0f / 9.0f, 1920.0f, 1080.0f);
            va.Bind();
            ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 3 * 2, GL_UNSIGNED_INT, nullptr));
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

