#pragma once

#include "Scene.h"
#include "ZicoMath.h"

class GameManagerScript;

class DongilScene : public Scene
{
public:
	using Scene::Scene;
	virtual void Enter() override;

public:
	void CreateWildBoar(GameManagerScript* gameManagerScript);

public:
	Vector2 m_StartPoint{ 960.f, 540.f };
};

