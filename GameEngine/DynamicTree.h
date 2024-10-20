#pragma once

#include "BroadPhase.h"
#include "CollisionDefine.h"
#include "Bound.h"
#include "Collider.h"
struct TreeNode
{
	TreeNode(void)
		: parent(nullptr)
		, data(nullptr)
		,childrenCrossed(false)
	{
		children[0] = nullptr;
		children[1] = nullptr;
	}

	bool IsLeaf(void) const
	{
		return children[0] == nullptr;
	}

	// 브랜치를 설정한다.
	void SetBranch(TreeNode* n0, TreeNode* n1)
	{
		n0->parent = this;
		n1->parent = this;

		children[0] = n0;
		children[1] = n1;
	}

	void SetLeaf(Collider* data)
	{
		// create two-way link
		this->data = data;
		data->SetUserdata(this);

		children[0] = nullptr;
		children[1] = nullptr;
	}

	/// 본인 말고 다른 형제를 들고온다.
	TreeNode* GetSibling(void) const
	{
		return this == parent->children[0]
			? parent->children[1]
			: parent->children[0];
	}



	void UpdateAABB(float margin)
	{
		if (IsLeaf())
		{
			// make fat AABB
			const Vector2 marginVec(margin, margin);
			box.lowerBound = data->GetBound().lowerBound - marginVec;
			box.upperBound = data->GetBound().upperBound + marginVec;
		}
		else
			// make union of child AABBs of child nodes
			box = children[0]->box.Union(children[1]->box);
	}



	/// 뚱뚱한 AABB를 저장한다. 
	Bound box;
	/// 엄마
	TreeNode* parent;
	/// 애기
	TreeNode* children[2];

	/// 실제 콜라이더의 포인터 저장
	Collider* data;

	/// childrenCrossed부울 플래그를 사용하여 분기 노드의 자식이 이미 "교차 검사(재귀 호출에 전달)"되었는지 확인합니다.
	bool childrenCrossed;



};

class DynamicTree : public BroadPhase
{
public:

	DynamicTree();
	~DynamicTree();
	

public:



	virtual void Add(Collider* col) override;

	virtual void Remove(Collider* col) override;
	
	virtual void Update() override;

	void UpdateNode(TreeNode* node);
	virtual const list<ColliderPair>& ComputePairs() override;

	virtual Collider* Pick(const Vector2& point) const override;

	virtual void Query(const Bound& bound, std::vector<Collider*>& output) const override;

	

private:
	/// 헬퍼 함수
	void UpdateNodeHelper(TreeNode* node, vector<TreeNode*>& invalidNodes);
	void InsertNode(TreeNode* node, TreeNode** parent);
	void RemoveNode(TreeNode* node);
	void ClearChildrenCrossFlagHelper(TreeNode* node);
	void ComputePairsHelper(TreeNode* n0, TreeNode* n1);
	void CrossChildren(TreeNode* node);
private:

	/// 트리의 루트
	TreeNode* m_Root;

	/// 큰 AABB를 벗어난 친구들
	vector<TreeNode*> m_InvalidNodes;

	/// 큰 AABB를 만들면서 설정할 여백 값
	float m_margin = 20.f;

	list<ColliderPair> m_Pairs;

	int leafcnt = 0;
};

