#pragma once

#include "include/GL/glew.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) Common::GL::ClearError();\
    x;\
    ASSERT(Common::GL::LogCall(#x, __FILE__, __LINE__))

namespace Common
{
    namespace GL
    {
        void ClearError();
        bool LogCall(const char* function, const char* file, int line);
    }
}
