#include "shader.hh"

#include <iostream>

#include "renderer.hh"

Common::GL::Shader::Shader(Common::GL::ShaderSource& shaderSource)
    :m_RendererID(0), m_ShaderSource(shaderSource)
{
    GLCall(m_RendererID = glCreateProgram());

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, shaderSource.VertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, shaderSource.FragmentSource);

    GLCall(glAttachShader(m_RendererID, vs));
    GLCall(glAttachShader(m_RendererID, fs));
    GLCall(glLinkProgram(m_RendererID));
    GLCall(glValidateProgram(m_RendererID));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
}

Common::GL::Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Common::GL::Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Common::GL::Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Common::GL::Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

unsigned int Common::GL::Shader::CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();

    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader! " << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

int Common::GL::Shader::GetUniformLocation(const std::string& name)
{
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist." << std::endl;
    return location;
}
