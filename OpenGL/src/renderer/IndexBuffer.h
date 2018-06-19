#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count; // Indices count
public:
	IndexBuffer(const unsigned int* data, unsigned int size);
	~IndexBuffer();

	void Delete() const;

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; } // Return indices count
};
