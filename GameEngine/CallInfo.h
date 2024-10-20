#pragma once

#include <any>
#include <functional>

class MonoBehaviour;

struct CallInfo
{
	MonoBehaviour* listener;
	std::function<void(std::any)> callbackFunc;

	bool operator==(const CallInfo& rhs) const
	{
		return this->listener == rhs.listener && &this->callbackFunc == &rhs.callbackFunc;
	}

};
