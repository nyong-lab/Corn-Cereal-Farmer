#pragma once
#include "Scene.h"
#include "ZicoMath.h"

class YoonseoTestScene :
    public Scene
{
private:
	using Scene::Scene;
	virtual void Enter() override;

private:
	//Vector2 m_StartPoint{ 482.f, 138.f };
};

