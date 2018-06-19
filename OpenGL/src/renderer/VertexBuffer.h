#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Delete() const;

	template<typename T> // template for passing different types into VertexAttribPointer -> GL_FLOAT, GL_SHORT, etc.
	void Push<T>(T type);

	void Bind() const;
	void Unbind() const;
};