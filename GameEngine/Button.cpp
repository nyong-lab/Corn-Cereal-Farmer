#include "pch.h"
#include "Button.h"

Button::Button(std::function<void(BUTTON_EVENT)> callbackFunction)
	: m_CallbackFuction(callbackFunction)
	, m_CurrentEvent(BUTTON_EVENT::DEFAULT)
{

}

Button::~Button()
{
}

void Button::Start()
{
}

void Button::Update(float deltaTime)
{
}

void Button::FixedUpdate(float deltaTime)
{
	UI::FixedUpdate(deltaTime);

	if (!m_MouseOn &&
		m_CurrentEvent != BUTTON_EVENT::DEFAULT)
	{
		m_CurrentEvent = BUTTON_EVENT::DEFAULT;
		m_CallbackFuction(BUTTON_EVENT::DEFAULT);
	}
}

void Button::Finalize()
{
}

void Button::MouseOn()
{
	if (m_CurrentEvent != BUTTON_EVENT::DOWN &&
		m_CurrentEvent != BUTTON_EVENT::HOVER)
	{
		m_CurrentEvent = BUTTON_EVENT::HOVER;
		m_CallbackFuction(BUTTON_EVENT::HOVER);
	}
}

void Button::MouseLeftButtonDown()
{
	m_CurrentEvent = BUTTON_EVENT::DOWN;
	m_CallbackFuction(BUTTON_EVENT::DOWN);
}

void Button::MouseLeftButtonClick()
{
	m_CallbackFuction(BUTTON_EVENT::CLICK);

	m_CurrentEvent = BUTTON_EVENT::HOVER;
	m_CallbackFuction(BUTTON_EVENT::HOVER);
}
