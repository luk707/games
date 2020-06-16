#pragma once

#include <string>
#include <unordered_map>

#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_source.hh"

namespace Common
{
    namespace GL
    {
        class Shader
        {
        private:
            unsigned int m_RendererID;
            std::unordered_map<std::string, unsigned int> m_UniformLocationCache;
        public:
            Shader(Common::GL::ShaderSource& shaderSource);
            ~Shader();

            void Bind() const;
            void Unbind() const;

            void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
            void SetUniformMat4(const std::string& name, glm::mat4x4& matrix);
        private:
            unsigned int CompileShader(unsigned int type, const std::string& source);
            int GetUniformLocation(const std::string& name);
        };
    }
}
