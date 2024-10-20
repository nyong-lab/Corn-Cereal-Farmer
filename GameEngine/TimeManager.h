#pragma once
class TimeManager
{
public:
	TimeManager();
	~TimeManager();

public:
	void Initailize();
	void Update();

public:
	void SetTimeScale(float timeScale) { m_TimeScale = timeScale; }
	float GetTimeScale() { return m_TimeScale; }
	void Pause() { m_IsPaused = 0; }
	void Resume() { m_IsPaused = 1; }

	float GetDeltaTime() { return (float)m_DeltaTime * m_TimeScale * m_IsPaused; }
	double GetDoubleDeltaTime() { return m_DeltaTime * m_TimeScale * m_IsPaused; }

private:
	LARGE_INTEGER m_PreviousCount;
	LARGE_INTEGER m_CurrentCount;
	LARGE_INTEGER m_Frequency;

	double m_DeltaTime;

	float m_TimeScale = 1.0f;
	int m_IsPaused = 1;

};

