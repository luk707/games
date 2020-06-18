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
        unsigned int verts = 26;
        float verticies[] = {
            40.0f, 0.0f, 95.0f,
			-40.0f, 0.0f, 95.0f,
			0.0f, 32.5f, 30.0f,
			-150.0f, -3.8f, -10.0f,
			150.0f, -3.8f, -10.0f,
			-110.0f, 20.0f, -50.0f,
			110.0f, 20.0f, -50.0f,
			160.0f, -10.0f, -50.0f,
			-160.0f, -10.0f, -50.0f,
			0.0f, 32.5f, -50.0f,
			-40.0f, -30.0f, -50.0f,
			40.0f, -30.0f, -50.0f,
			-45.0f, 10.0f, -50.1f,
			-10.0f, 15.0f, -50.1f,
			10.0f, 15.0f, -50.1f,
			45.0f, 10.0f, -50.1f,
			45.0f, -15.0f, -50.1f,
			10.0f, -20.0f, -50.1f,
			-10.0f, -20.0f, -50.1f,
			-45.0f, -15.0f, -50.1f,
			-100.0f, -7.5f, -50.1f,
			-100.0f, 7.5f, -50.1f,
			-110.0f, 0.0f, -50.1f,
			100.0f, 7.5f, -50.1f,
			110.0f, 0.0f, -50.1f,
			100.0f, -7.5f, -50.1f,
        };

        unsigned int tris = 20;
        unsigned int tri_indicies[] = {
            2, 0, 1,
            0, 11, 1,
            1, 11, 10,
            6, 0, 2,
            6, 4, 0,
            0, 4, 11,
            11, 4, 7,
            5, 2, 1,
            5, 1, 3,
            8, 5, 3,
            6, 7, 4,
            6, 2, 9,
            9, 2, 5,
            1, 10, 3,
            3, 10, 8,
            10, 5, 8,
            9, 5, 10,
            11, 9, 10,
            11, 6, 9,
            7, 6, 11
        };
        unsigned int lines = 38;
        unsigned int wireframe_indicies[] = {
            2, 1,
            1, 0,
            0, 2,
            1, 10,
            0, 11,
            0, 6,
            6, 2,
            0, 4,
            4, 6,
            7, 4,
            1, 5,
            5, 2,
            1, 3,
            3, 5,
            10, 8,
            8, 3,
            2, 9,
            9, 6,
            6, 7,
            7, 11,
            11, 10,
            10, 8,
            8, 5,
            5, 9,
            14, 15,
            15, 16,
            16, 17,
            17, 14,
            12, 13,
            13, 18,
            18, 19,
            19, 12,
            23, 24,
            24, 25,
            25, 23,
            22, 21,
            21, 20,
            20, 22,
        };
        Common::GL::VertexArray va;
        Common::GL::VertexBuffer vb(verticies, verts * 3 * sizeof(float));
        Common::GL::VertexBufferLayout layout;
        layout.Push<float>(3); // XYZ
        va.AddBuffer(vb, layout);
        Common::GL::IndexBuffer tri_ib(tri_indicies, 3 * tris);
        Common::GL::IndexBuffer wireframe_ib(wireframe_indicies, 2 * lines);

        glm::mat4x4 proj = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.f);
        glm::mat4x4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -400.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        float previous = glfwGetTime();

        float xRot = 0;
        float yRot = 0;
        float zRot = 0;

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
            xRot += 0.4f * delta;
            yRot += 0.4f * delta;
            zRot += 0.4f * delta;
            rot = glm::quat(glm::vec3(xRot, yRot, zRot));

            // Render geometery
            shader.Bind();
            shader.SetUniformMat4("u_Proj", proj);
            shader.SetUniformMat4("u_View", view);
            shader.SetUniformMat4("u_Model", glm::toMat4(rot));
            shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);
            va.Bind();
            tri_ib.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 3 * tris, GL_UNSIGNED_INT, nullptr));

            wireframe_ib.Bind();
            shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            shader.SetUniformMat4("u_Model", glm::translate(glm::identity<glm::mat4x4>(), glm::vec3(0.0f, 0.0f, -0.01f)) * glm::toMat4(rot));
            GLCall(glDrawElements(GL_LINES, 2 * lines, GL_UNSIGNED_INT, nullptr));

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

