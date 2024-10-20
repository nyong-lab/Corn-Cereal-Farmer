#pragma once

#include "GameObject.h"

class ImageRenderer;
class TextRenderer;

class QuestList : public GameObject
{
public:
	QuestList();
	~QuestList();

public:
	static const int QUESTCOUNT = 4;

public:
	ImageRenderer* m_CheckBoxImage[QUESTCOUNT];
	TextRenderer* m_QuestText[QUESTCOUNT];

private:
	GameObject* m_Quest[QUESTCOUNT];
};


