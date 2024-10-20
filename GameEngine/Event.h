#pragma once

#include <any>

class GameObject;


class Event
{
public:
	Event(string eventID, std::any parameter = nullptr);
	~Event();

	
	string GetEventID() const { return m_EventID; }
	std::any GetParameter() { return m_Parameter; }
private:
	string m_EventID;
	std::any m_Parameter;
};

