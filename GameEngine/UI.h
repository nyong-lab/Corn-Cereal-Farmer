/// [2023/8/9] 박연하
/// --------------------------
/// Component를 상속받은 UI
/// 모든 UI의 부모 클래스이다

#pragma once

#include "../Math/Vector2.h"
#include "Component.h"

class UI : public Component
{
public:
	UI();
	virtual ~UI();

public:
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
	virtual void Render() override;
	virtual void Finalize() override;

public:
	// Getter & Setter
	bool GetMouseOn() { return m_MouseOn; }
	void SetLeftButtonDown(bool isBtnDown) { m_LeftButtonDown = isBtnDown; }

public:
	virtual void MouseOn();
	virtual void MouseLeftButtonDown();
	virtual void MouseLeftButtonUp();
	virtual void MouseLeftButtonClick();

	void MouseOnCheck();

protected:
	UI* m_parentUI;

	Vector2 m_FinalPosition;	// UI의 최종 좌표 위치

	bool m_MouseOn;				// UI 위에 마우스가 있는지
	bool m_LeftButtonDown;		// UI에 왼쪽 버튼이 눌린 적 있는지

	friend class UIManager;
};