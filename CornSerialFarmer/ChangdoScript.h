#pragma once
#include "MonoBehaviour.h"

class Collider;
class TextRenderer;
class GameManagerScript;

class ChangdoScript :
    public MonoBehaviour
{
public:
	ChangdoScript();
	~ChangdoScript();

	void WareHouseGameFunc(std::any);
	void CornGameFunc(std::any);
	void WildBoarGameFunc(std::any);
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;


public:
	Collider* m_Collider = nullptr;
	TextRenderer* m_Render = nullptr;
	GameManagerScript* m_GameManagerScript = nullptr;
};

