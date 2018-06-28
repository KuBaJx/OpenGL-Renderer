#include "VertexArray.h"
#include "../misc/Assert.h"

// VertexBufferObject - used for tie together vertex arrays with layout ( so we know what the layout of the vertex buffer acutally is )
VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::BindArray() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnbindArray() const
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout)
{
	BindArray();
	buffer.Bind();
	const auto& elements = layout.GetVertexBufferElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset)); // Link specified layout to vertex buffer
		offset += element.count * VertexBufferElements::GetSizeOfType(element.type); // Offset of each element in buffer - so if we have multiple buffers in one VAO, we can offset them
	}
}