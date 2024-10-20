#include "pch.h"
#include "ImageUI.h"
#include "GameObject.h"

/// <param name="image">UI�� ����� �̹��� �ε�</param>
/// <param name="imageOffset">�̹��� ������ ����</param>
/// <param name="slicePos">��Ʈ���� �߶󳻴� ��ġ ���� �ʿ��� ��</param>
ImageUI::ImageUI(Vector2 size, ID2D1Bitmap* image, bool imageChangeMode, Vector2 imageOffset, Vector2 slicePos)
	: UI(size)
	, m_Image(image)
	, m_ImageOffset(imageOffset)
	, m_SlicePos(slicePos)
	, m_ImageChangeMode(imageChangeMode)
	, m_ImageChange(IMAGE_EVENT::DEFALUT)
	, m_beforeImageState(IMAGE_EVENT::DEFALUT)
{
}

ImageUI::~ImageUI()
{
}

void ImageUI::Render()
{	
	UI::Render();

	GraphicsEngine::GetInstance()->ShowImage(
		m_Image,
		m_ImageOffset.x, m_ImageOffset.y,
		m_SlicePos.x + (m_Size.x * (int)m_ImageChange), m_SlicePos.y,
		m_Size.x, m_Size.y);
}

void ImageUI::FixedUpdate(float deltatime)
{
	UI::FixedUpdate(deltatime);

	if (!m_ImageChangeMode) return;
	if (!m_MouseOn)
		m_ImageChange = m_beforeImageState = IMAGE_EVENT::DEFALUT;
}

void ImageUI::MouseOn()
{
 	m_parentUI->MouseOn();

	if (!m_ImageChangeMode) return;
	if (m_beforeImageState != IMAGE_EVENT::LBTDOWN)
		m_ImageChange = m_beforeImageState = IMAGE_EVENT::HOVER;
}

void ImageUI::MouseLeftButtonDown()
{
	m_parentUI->MouseLeftButtonDown();

	if (!m_ImageChangeMode) return;
	m_ImageChange = m_beforeImageState = IMAGE_EVENT::LBTDOWN;

}

void ImageUI::MouseLeftButtonUp()
{
	m_parentUI->MouseLeftButtonUp();

	if (!m_ImageChangeMode) return;
	m_ImageChange = IMAGE_EVENT::HOVER;
	m_beforeImageState = IMAGE_EVENT::LBTDOWN;

}

void ImageUI::MouseLeftButtonClick()
{
	m_parentUI->MouseLeftButtonClick();

	if (!m_ImageChangeMode) return;
	m_ImageChange = IMAGE_EVENT::HOVER;
	m_beforeImageState = IMAGE_EVENT::LBTCLICK;
}
