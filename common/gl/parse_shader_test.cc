#include <iostream>
#include "gtest/gtest.h"

#include "parse_shader.hh"

TEST(ParseShaderTest) {
    std::string shaderSource =
        "#shader vertex\n"
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n"
        "\n"
        "#shader fragment\n"
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n"
        "\n";

    std::string expectedVertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n"
        "\n";

    std::string expectedFragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n"
        "\n";

    std::stringstream shaderSourceStream;
    shaderSourceStream << shaderSource;

    Common::GL::ShaderSource programSource = Common::GL::ParseShader(shaderSourceStream);

    EXPECT_EQ(programSource.VertexSource, expectedVertexShader);
    EXPECT_EQ(programSource.FragmentSource, expectedFragmentShader);
}
