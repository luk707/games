#include "renderer.hh"

#include <iostream>

void Common::GL::ClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool Common::GL::LogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (0x" << std::hex << error << "): " << function << " " << file << ":" << std::dec << line << std::endl;
        return false;
    }
    return true;
}
