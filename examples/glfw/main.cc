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
        float verticies[] = {
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f
        };
        unsigned int indicies[] = {
            0, 2, 1,
            1, 2, 3,
            4, 6, 0,
            0, 6, 2,
            6, 7, 2,
            2, 7, 3,
            5, 1, 7,
            7, 1, 3,
            4, 0, 5,
            5, 0, 1,
            7, 6, 5,
            5, 6, 4
        };
        Common::GL::VertexArray va;
        Common::GL::VertexBuffer vb(verticies, 8 * 7 * sizeof(float));
        Common::GL::VertexBufferLayout layout;
        layout.Push<float>(3); // XYZ
        layout.Push<float>(4); // RGBA
        va.AddBuffer(vb, layout);
        Common::GL::IndexBuffer ib(indicies, 3 * 12);

        float r = 0.0f;
        float increment = 0.05f;

        glm::mat4x4 proj = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
        glm::mat4x4 view;
        glm::mat4x4 model = glm::identity<glm::mat4x4>();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.4f, 0.6f, 0.9f, 1.0f);

            // Calculate view
            view = glm::lookAt(glm::vec3(sinf(r) * 4.0f, 4.0f, cosf(r) * 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            
            // Render geometery
            shader.Bind();
            shader.SetUniformMat4("u_Proj", proj);
            shader.SetUniformMat4("u_View", view);
            shader.SetUniformMat4("u_Model", model);
            va.Bind();
            ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, nullptr));

            if (r > 20.0f)
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

