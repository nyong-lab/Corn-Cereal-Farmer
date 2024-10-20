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

	// �귣ġ�� �����Ѵ�.
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

	/// ���� ���� �ٸ� ������ ���´�.
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



	/// �׶��� AABB�� �����Ѵ�. 
	Bound box;
	/// ����
	TreeNode* parent;
	/// �ֱ�
	TreeNode* children[2];

	/// ���� �ݶ��̴��� ������ ����
	Collider* data;

	/// childrenCrossed�ο� �÷��׸� ����Ͽ� �б� ����� �ڽ��� �̹� "���� �˻�(��� ȣ�⿡ ����)"�Ǿ����� Ȯ���մϴ�.
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
	/// ���� �Լ�
	void UpdateNodeHelper(TreeNode* node, vector<TreeNode*>& invalidNodes);
	void InsertNode(TreeNode* node, TreeNode** parent);
	void RemoveNode(TreeNode* node);
	void ClearChildrenCrossFlagHelper(TreeNode* node);
	void ComputePairsHelper(TreeNode* n0, TreeNode* n1);
	void CrossChildren(TreeNode* node);
private:

	/// Ʈ���� ��Ʈ
	TreeNode* m_Root;

	/// ū AABB�� ��� ģ����
	vector<TreeNode*> m_InvalidNodes;

	/// ū AABB�� ����鼭 ������ ���� ��
	float m_margin = 20.f;

	list<ColliderPair> m_Pairs;

	int leafcnt = 0;
};

