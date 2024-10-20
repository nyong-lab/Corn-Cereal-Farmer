/// [2023/8/18] 박연하
/// --------------------------
/// 게임의 이펙트를 관리하는 매니저

#pragma once

#include "MonoBehaviour.h"

class EffectManagerScript : public MonoBehaviour
{
public:
	EffectManagerScript();
	~EffectManagerScript();

public:
	virtual void Start();
	virtual void Update(float deltaTime);

public:
	void ApplyTimeFlowEffect(
		float temperature,
		float colorTint,
		float brightness);
};

