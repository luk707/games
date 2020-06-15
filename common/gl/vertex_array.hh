#pragma once

#include "vertex_buffer.hh"
#include "vertex_buffer_layout.hh"

namespace Common
{
    namespace GL
    {
        class VertexArray
        {
        private:
            unsigned int m_RendererID;
        public:
            VertexArray();
            ~VertexArray();

            void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

            void Bind() const;
            void Unbind() const;
        };
    }
}
