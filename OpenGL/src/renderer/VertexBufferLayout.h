#pragma once

#include <vector>
#include <GL/glew.h>

struct VertexBufferElements
{
	unsigned int type;
	unsigned int count;
	bool normalized;
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElements> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	// Just template for specifications below
	template<typename T>
	void Push(int count)
	{
		static_assert(false);
	}

	// Used for passing floats into VertexAttribPointer
	template<>
	void Push<float>(int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, false }); // Type, Count, Normalized
	}

	// Used for passing unsigned ints into VertexAttribPointer
	template<>
	void Push<unsigned int>(int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, false }); // Type, Count, Normalized
	}

	inline std::vector<VertexBufferElements> GetVertexBufferElements() const { return m_Elements; } // fix to return const&
	inline unsigned int GetStride() const { return m_Stride; }
};