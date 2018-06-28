#pragma once

#include <vector>
#include "../misc/Assert.h"
#include <GL/glew.h>

struct VertexBufferElements
{
	unsigned int type;
	unsigned int count;
	char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(GLfloat);
			break;
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);
			break;
		case GL_UNSIGNED_BYTE:
			return sizeof(GLubyte);
			break;
		}

		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElements> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	// Just template for specifications below
	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	// Used for passing floats into VertexAttribPointer
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE }); // Type, Count, Normalized
		m_Stride += VertexBufferElements::GetSizeOfType(GL_FLOAT) * count; // 4 bytes offset of each element
	}

	// Used for passing unsigned ints into VertexAttribPointer
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE }); // Type, Count, Normalized
		m_Stride += VertexBufferElements::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE }); // Type, Count, Normalized
		m_Stride += VertexBufferElements::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferElements>& GetVertexBufferElements() const { return m_Elements; } // fix to return const&
	inline unsigned int GetStride() const { return m_Stride; }
};