#include "pch.h"
#include "TimeManager.h"

TimeManager::TimeManager() :
	m_CurrentCount{},
	m_PreviousCount{},
	m_Frequency{},
	m_DeltaTime(0.f)
{

}

TimeManager::~TimeManager()
{

}

void TimeManager::Initailize()
{
	QueryPerformanceCounter(&m_PreviousCount);
	QueryPerformanceFrequency(&m_Frequency);

}

void TimeManager::Update()
{
	QueryPerformanceCounter(&m_CurrentCount);
	m_DeltaTime = (double)(m_CurrentCount.QuadPart - m_PreviousCount.QuadPart) / (double)m_Frequency.QuadPart;

	m_PreviousCount = m_CurrentCount;
}