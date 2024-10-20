#pragma once
#include "MonoBehaviour.h"

class Animator;
class Camera;

class BubblePopScript :
    public MonoBehaviour
{
public:
	BubblePopScript();
	~BubblePopScript();
public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Finalize() override;


public:
	std::vector<Animator*> m_NPCBubble;
	std::vector<Animator*> m_BubbleUI;
	Camera* m_Camera = nullptr;
};

