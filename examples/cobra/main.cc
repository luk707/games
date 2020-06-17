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
#include <glm/gtx/quaternion.hpp>

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
        std::ifstream stream("examples/cobra/cobra.glsl");

        if (!stream)
        {
            std::cout << "Cannot open file!" << std::endl;
            exit(EXIT_FAILURE);
        }

        Common::GL::ShaderSource shaderSource = Common::GL::ParseShader(stream);
        Common::GL::Shader shader(shaderSource);

        // Setup vertex array, vertex buffer and index buffer
        float verticies[] = {
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
        };
        unsigned int tri_indicies[] = {
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
        unsigned int wireframe_indicies[] = {
            0, 1,
            1, 3,
            3, 2,
            2, 0,
            0, 4,
            1, 5,
            2, 6,
            3, 7,
            4, 5,
            5, 7,
            7, 6,
            6, 4
        };
        Common::GL::VertexArray va;
        Common::GL::VertexBuffer vb(verticies, 8 * 7 * sizeof(float));
        Common::GL::VertexBufferLayout layout;
        layout.Push<float>(3); // XYZ
        va.AddBuffer(vb, layout);
        Common::GL::IndexBuffer tri_ib(tri_indicies, 3 * 12);
        Common::GL::IndexBuffer wireframe_ib(wireframe_indicies, 2 * 12);

        glm::mat4x4 proj = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 100.f);
        glm::mat4x4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        float previous = glfwGetTime();

        float xRot;
        float yRot;
        float zRot;

        glm::quat rot = glm::identity<glm::quat>();

        while (!glfwWindowShouldClose(window))
        {
            // common part, do this only once
            float now = glfwGetTime();
            float delta = now - previous;
            previous = now;

            // glClear(GL_DEPTH_BUFFER_BIT);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            // Calculate rotation
            xRot += 1.0f * delta;
            yRot += 1.0f * delta;
            zRot += 1.0f * delta;
            rot = glm::quat(glm::vec3(xRot, yRot, zRot));

            // Render geometery
            shader.Bind();
            shader.SetUniformMat4("u_Proj", proj);
            shader.SetUniformMat4("u_View", view);
            shader.SetUniformMat4("u_Model", glm::toMat4(rot));
            shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);
            va.Bind();
            tri_ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, nullptr));

            wireframe_ib.Bind();
            shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            shader.SetUniformMat4("u_Model", glm::translate(glm::identity<glm::mat4x4>(), glm::vec3(0.0f, 0.0f, -0.01f)) * glm::toMat4(rot));
            GLCall(glDrawElements(GL_LINES, 2 * 12, GL_UNSIGNED_INT, nullptr));

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

