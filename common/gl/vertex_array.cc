#include "vertex_array.hh"

#include "renderer.hh"

Common::GL::VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

Common::GL::VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void Common::GL::VertexArray::AddBuffer(const Common::GL::VertexBuffer& vb, const Common::GL::VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
        offset += element.count * Common::GL::VertexBuffferElement::GetSizeOfType(element.type);
    }
}

void Common::GL::VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void Common::GL::VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}
