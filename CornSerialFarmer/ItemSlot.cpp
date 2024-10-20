#include "ItemSlot.h"
#include "Define.h"

#include "Transform.h"

#include "ResourceManager.h"
#include "Image.h"
#include "Font.h"

#include "UI.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "Panel.h"

ItemSlot::ItemSlot()
	: GameObject("ItemSlot", OBJECT_TYPE::UI)
{
	// Set Position & Size
	GetTransform()->SetLocalPosition(Vector2(960.f, 970.f));
	GetTransform()->SetSize(Vector2(688.f, 161.f));

	// Empty UI
	UI* itemSlotBaseUI = new Panel();
	AddComponent(itemSlotBaseUI);

	// Item Slot Base Image
	ImageRenderer* itemSlotBaseImage = new ImageRenderer(
		ResourceManager::GetInstance()->LoadResource<Image>(L"ItemSlotBaseImage", L"/UI/itemslotBase.png")->GetImage());
	AddComponent(itemSlotBaseImage);

	/// Item Slot
	for (int slotNum = 0; slotNum < SLOTCOUNT; slotNum++)
	{
		string itemSlotName = "ItemSlot" + to_string(slotNum);
		m_ItemSlot[slotNum] = new GameObject(itemSlotName, OBJECT_TYPE::UI);
		AddObjectChild(m_ItemSlot[slotNum]);

		// Set Position & Size
		Transform* itemSlotTransform = m_ItemSlot[slotNum]->GetTransform();

		float slotPosition = 0.f;
		switch (slotNum) {
		case 0: slotPosition = -260.f; break;
		case 1: slotPosition = -130.f; break;
		case 2: slotPosition = 0.f; break;
		case 3: slotPosition = 130.f; break;
		case 4: slotPosition = 260.f; break;
		default: break; 
		}

		itemSlotTransform->SetLocalPosition(Vector2(slotPosition, 0.f));
		itemSlotTransform->SetSize(Vector2(120.f, 120.f));

		// Empty UI
		UI* itemSlotUI = new Panel();
		m_ItemSlot[slotNum]->AddComponent(itemSlotUI);

		// Item Slot Image
		m_ItemSlotImage[slotNum] = new ImageRenderer(
			ResourceManager::GetInstance()->LoadResource<Image>(L"ItemSlot", L"/UI/itemslot.png")->GetImage());
		m_ItemSlot[slotNum]->AddComponent(m_ItemSlotImage[slotNum]);

		/// Item
		string itemName = "Item" + to_string(slotNum);
		item[slotNum] = new GameObject(itemName, OBJECT_TYPE::UI);
		m_ItemSlot[slotNum]->AddObjectChild(item[slotNum]);

		// Set Size
		item[slotNum]->GetTransform()->SetSize(Vector2(64.f, 64.f));

		// Empty UI
		UI* itemUI = new Panel();
		item[slotNum]->AddComponent(itemUI);

		// Item Slot Image
		m_ItemImage[slotNum] = new ImageRenderer(
			ResourceManager::GetInstance()->LoadResource<Image>(L"Empty", L"/Image/item/none.png")->GetImage());
		item[slotNum]->AddComponent(m_ItemImage[slotNum]);

		/// Item Count Text
		string textCountName = "ItemCountText" + to_string(slotNum);
		itemCountText[slotNum] = new GameObject(textCountName, OBJECT_TYPE::UI);
		item[slotNum]->AddObjectChild(itemCountText[slotNum]);

		// Empty UI
		UI* itemCountTextUI = new Panel();
		itemCountText[slotNum]->AddComponent(itemCountTextUI);

		// Item Text Renderer
		m_ItemCountText[slotNum] = new TextRenderer(
			Vector2(46.f, 18.f),
			L"",
			ResourceManager::GetInstance()->LoadResource<Font>(L"BitBit18", L"/Font/DNFBitBitTTF.ttf", L"던파 비트비트체 TTF", 18.f)->Getfont(),
			COLOR::WHITE);
		ResourceManager::GetInstance()->LoadResource<Font>(L"BitBit18")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		ResourceManager::GetInstance()->LoadResource<Font>(L"BitBit18")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_TRAILING);
		
		m_ItemCountText[slotNum]->SetTextAlignRight();
		itemCountText[slotNum]->AddComponent(m_ItemCountText[slotNum]);

		/// Item Name Text
		string textItemName = "ItemNameText" + to_string(slotNum);
		itemNameText[slotNum] = new GameObject(textItemName, OBJECT_TYPE::UI);
		itemNameText[slotNum]->GetTransform()->SetSize(Vector2(76.f, 27.f));
		item[slotNum]->AddObjectChild(itemNameText[slotNum]);

		// Empty UI
		UI* itemNameTextUI = new Panel();
		itemNameText[slotNum]->AddComponent(itemNameTextUI);

		// Item Text Box Image
		m_ItemNameBox[slotNum] = new ImageRenderer(
			ResourceManager::GetInstance()->LoadResource<Image>(L"NameBox", L"/UI/namebox.png")->GetImage(),
			Vector2(0.f, -104.f));
		itemNameText[slotNum]->AddComponent(m_ItemNameBox[slotNum]);

		// Item Text Renderer
		m_ItemNameText[slotNum] = new TextRenderer(
			Vector2(0.f, -125.f),
			L"Name",
			ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16", L"/Font/Galmuri9.ttf", L"Galmuri9", 16.f)->Getfont(),
			COLOR::WHITE);
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetHorizontalAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		ResourceManager::GetInstance()->LoadResource<Font>(L"Galmuri9_16")->SetVerticalAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_ItemNameText[slotNum]->SetTextAlignMiddle();
		itemNameText[slotNum]->AddComponent(m_ItemNameText[slotNum]);
	}
}

ItemSlot::~ItemSlot()
{

}
