/// [2023/8/10] 박연하
/// --------------------------
/// 버튼! 콜백함수를 써보자

#pragma once

#include "UI.h"
#include <functional>

enum class BUTTON_EVENT
{
	DEFAULT,
	HOVER,
	DOWN,
	UP,
	CLICK,
};

class Button : public UI
{
public:
	Button(std::function<void(BUTTON_EVENT)> callbackFunction);
	virtual ~Button();

public:
	void Start() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float deltaTime) override;
	void Finalize() override;

public:
	void MouseOn() override;
	void MouseLeftButtonDown() override;
	void MouseLeftButtonClick() override;

private:
	std::function<void(BUTTON_EVENT)> m_CallbackFuction;

	BUTTON_EVENT m_CurrentEvent;
};

