#pragma once

#include "MonoBehaviour.h"

class ObjectDataScript : public MonoBehaviour
{
public:
	ObjectDataScript(int id);
	~ObjectDataScript();

public:
	virtual void Update(float deltaTime) override;

public:
	void SetId(int id) { this->id = id; }
	
public:
	int id;
	bool isDeadBodyHave;
	bool inabilityGetWater;
	int interactionArrowCount;
};

