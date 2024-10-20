#pragma once
#include "MonoBehaviour.h"
class WareHouseGameScript :
    public MonoBehaviour
{
public:
    WareHouseGameScript();
    ~WareHouseGameScript();
	void CountDownEnd(std::any);
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;

public:

};

