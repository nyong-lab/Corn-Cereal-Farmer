#pragma once
#include "MonoBehaviour.h"
class Move :
    public MonoBehaviour
{
public:
	Move();
	~Move();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
};

