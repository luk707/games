#pragma once

#include <string>

#include "shader_source.hh"

namespace Common
{
    namespace GL
    {
        class Shader
        {
        private:
            unsigned int m_RendererID;
            ShaderSource m_ShaderSource;
            // Uniform cache
        public:
            Shader(Common::GL::ShaderSource& shaderSource);
            ~Shader();

            void Bind() const;
            void Unbind() const;

            void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        private:
            unsigned int CompileShader(unsigned int type, const std::string& source);
            int GetUniformLocation(const std::string& name);
        };
    }
}