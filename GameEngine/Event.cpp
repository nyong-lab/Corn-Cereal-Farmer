#include "pch.h"
#include "Event.h"

Event::Event(string eventID, std::any parameter /*= nullptr*/) :
	m_EventID(eventID), 
	m_Parameter(parameter)
{

}

Event::~Event()
{

}
