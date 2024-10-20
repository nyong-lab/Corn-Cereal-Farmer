#include "EffectManagerScript.h"
#include "../GraphicsEngine/GraphicsEngine.h"

EffectManagerScript::EffectManagerScript()
	: MonoBehaviour(typeid(this).name())
{

}

EffectManagerScript::~EffectManagerScript()
{

}

void EffectManagerScript::Start()
{

}

void EffectManagerScript::Update(float deltaTime)
{

}

void EffectManagerScript::ApplyTimeFlowEffect(
	float temperature,
	float colorTint,
	float brightness)
{
	GraphicsEngine::GetInstance()->SetTemperatureValue(temperature);
	GraphicsEngine::GetInstance()->SetColorTintValue(colorTint);
	GraphicsEngine::GetInstance()->SetWhiteCurvePoint(Vector2(brightness, 0.f));
	GraphicsEngine::GetInstance()->SetBlackCurvePoint(Vector2(0.f, brightness));
}



