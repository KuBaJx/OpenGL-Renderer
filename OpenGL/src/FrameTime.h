#pragma once

class FrameTime
{
public:
	FrameTime();
	~FrameTime();

	void GetFrameTime();

private:
	double m_lastTime;
	double m_currentTime;
	int m_numFrames;
};