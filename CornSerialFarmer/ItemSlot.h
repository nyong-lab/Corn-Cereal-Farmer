#pragma once

#include "GameObject.h"

class ImageRenderer;
class TextRenderer;

class ItemSlot : public GameObject
{
public:
	ItemSlot();
	~ItemSlot();

public:
	static const int SLOTCOUNT = 5;

public:
	ImageRenderer* m_ItemSlotImage[SLOTCOUNT];
	ImageRenderer* m_ItemImage[SLOTCOUNT];
	TextRenderer* m_ItemCountText[SLOTCOUNT];
	ImageRenderer* m_ItemNameBox[SLOTCOUNT];
	TextRenderer* m_ItemNameText[SLOTCOUNT];

private:
	GameObject* m_ItemSlot[SLOTCOUNT];
	GameObject* item[SLOTCOUNT];
	GameObject* itemCountText[SLOTCOUNT];
	GameObject* itemNameText[SLOTCOUNT];
};

