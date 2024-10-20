/// [2023/8/15] 박연하
/// --------------------------
/// 아이템을 관리하는 아이템 매니저
/// 아이템을 보여주는 UI를 함께 관리한다

#pragma once

#include "MonoBehaviour.h"
#include <vector>

class ItemSlot;

enum class ITEM_TYPE
{
	AX,
	BAG,
	CATFOOD,
	CORN,
	FERTILIZER,
	FIREWOOD,
	SEED,
	EMPTYWATERING,
	WATERING,
	KEY,

	END
};

class Item
{
public:
	Item(std::wstring itemKeyName,
		std::wstring itemName,
		ITEM_TYPE itemType,
		bool isCountable,
		int itemCount = 1);
	~Item();

public:
	void SetItemCount(int itemCount) { m_ItemCount = itemCount; }
	void SetItemFocus(bool isFocus) { m_ItemFocus = isFocus; }
	
public:
	std::wstring m_ItemKeyName;	// 아이템의 키 이름
	std::wstring m_ItemName;	// 아이템의 이름
	ITEM_TYPE m_ItemType;		// 아이템의 종류
	bool m_ItemFocus;			// 포커싱 여부
	bool m_IsCountable;			// 셀 수 있는 아이템인지
	int m_ItemCount;			// 아이템의 개수
};

class ItemManagerScript : public MonoBehaviour
{
public:
	ItemManagerScript();
	~ItemManagerScript();

public:
	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Finalize();

public:
	void FindFocusItem();
	void ApplyItemSlot();
	void AddItem(Item* item);
	void DeleteItem(Item* item);
	void DeleteAllItem();

public:
	// Getter & Setter
	Item* GetCurrentFocusItem() { return m_ItemList[m_CurrentFocusItemIndex]; 
	}

public:
	static const int SLOTCOUNT = 5;
	std::vector<Item*> m_ItemList;

	// 아이템 슬롯 UI
	ItemSlot* m_ItemSlot;

	// 현재 포커싱된 아이템 인덱스
	int m_CurrentFocusItemIndex;
	bool m_ChangeFocus;

};

