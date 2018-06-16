#include "FrameTime.h"
#include "StdAfx.h"

FrameTime::FrameTime()
{
	m_lastTime = 0;
	m_numFrames = 0;
	m_currentTime = 0;
}

FrameTime::~FrameTime()
{

}

void FrameTime::GetFrameTime()
{
	m_currentTime = glfwGetTime();
	m_numFrames++;
	if (m_currentTime - m_lastTime >= 1.0) // If last log was more than 1 sec ago
	{
		// print and reset timer
		std::cout << 1000.0 / (double)m_numFrames << " ms/frame" << std::endl;
		m_numFrames = 0;
		m_lastTime += 1.0;
	}
}