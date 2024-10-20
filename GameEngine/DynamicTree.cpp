#include "pch.h"
#include "DynamicTree.h"

DynamicTree::DynamicTree() :
	m_Root(nullptr)
{
}

DynamicTree::~DynamicTree()
{
	if (m_Root)
	{
		while (m_Root->children[0] || m_Root->children[1])
		{
			if (m_Root->children[0])
				RemoveNode(m_Root->children[0]);
			if (m_Root->children[1])
				RemoveNode(m_Root->children[0]);
		}
		RemoveNode(m_Root);
	}
	m_Pairs.clear();
}

void DynamicTree::Add(Collider* data)
{
	if (m_Root)
	{
		// not first node, insert node to tree
		TreeNode* node = new TreeNode();
		node->SetLeaf(data);
		node->UpdateAABB(m_margin);
		InsertNode(node, &m_Root);
	}
	else
	{
		// first node, make root
		m_Root = new TreeNode();
		m_Root->SetLeaf(data);
		m_Root->UpdateAABB(m_margin);
	}
}

void DynamicTree::Remove(Collider* col)
{
	TreeNode* node = any_cast<TreeNode* >(col->GetUserdata());
		
	// remove two-way link
	node->data = nullptr;
	col->SetUserdata(nullptr);

	RemoveNode(node);
}

void DynamicTree::Update()
{
	if (m_Root)
	{
		if (m_Root->IsLeaf())
			m_Root->UpdateAABB(m_margin);
		else
		{
			// grab all invalid nodes
			m_InvalidNodes.clear();
			UpdateNodeHelper(m_Root, m_InvalidNodes);

			// re-insert all invalid nodes
			for (TreeNode* node : m_InvalidNodes)
			{
				// grab parent link
				// (pointer to the pointer that points to parent)
				TreeNode* parent = node->parent;
				TreeNode* sibling = node->GetSibling();
				TreeNode** parentLink =
					parent->parent ? (
						parent == parent->parent->children[0]
						? &parent->parent->children[0]
						: &parent->parent->children[1]
						)
					: &m_Root;

				// replace parent with sibling
				sibling->parent =
					parent->parent
					? parent->parent
					: nullptr; // root has null parent

				*parentLink = sibling;
				delete parent;
				UpdateNode(sibling->parent);

				// re-insert node
				node->UpdateAABB(m_margin);
				InsertNode(node, &m_Root);
			}
			m_InvalidNodes.clear();
		}
	}
}

void DynamicTree::UpdateNode(TreeNode* node)
{
	if (!node) return;

	node->UpdateAABB(m_margin);
	UpdateNode(node->parent);
}

const list<DynamicTree::ColliderPair>& DynamicTree::ComputePairs()
{

	list<DynamicTree::ColliderPair>().swap(m_Pairs);
	m_Pairs.clear();

	// early out
	if (!m_Root || m_Root->IsLeaf())
		return m_Pairs;

	// clear Node::childrenCrossed flags
	ClearChildrenCrossFlagHelper(m_Root);

	leafcnt = 0;
	// base recursive call
	ComputePairsHelper(m_Root->children[0],
		m_Root->children[1]);

	return m_Pairs;
}

Collider* DynamicTree::Pick(const Vector2& point) const
{
	return nullptr;
}

void DynamicTree::Query(const Bound& bound, std::vector<Collider*>& output) const
{
// 	for (auto& pair : m_Pairs)
// 	{
// 		if(bound.Intersects(pair.first->GetBound()) 
// 		if(bound.Intersects(pair.second->get)
// 	}
		
}

void DynamicTree::UpdateNodeHelper(TreeNode* node, vector<TreeNode*>& invalidNodes)
{


	if (node->IsLeaf())
	{
		// check if fat AABB doesn't 
		// contain the collider's AABB anymore
		if (!node->box.Contains(node->data->GetBound()))
			invalidNodes.push_back(node);
	}
	else
	{
		UpdateNodeHelper(node->children[0], invalidNodes);
		UpdateNodeHelper(node->children[1], invalidNodes);
	}

}

void DynamicTree::InsertNode(TreeNode* node, TreeNode** parent)
{
	TreeNode* p = *parent;
	if (p->IsLeaf())
	{
		// parent is leaf, simply split
		TreeNode* newParent = new TreeNode();
		newParent->parent = p->parent;
		newParent->SetBranch(node, p);
		*parent = newParent;
	}
	else
	{
		// parent is branch, compute volume differences 
		// between pre-insert and post-insert
		const Bound aabb0 = p->children[0]->box;
		const Bound aabb1 = p->children[1]->box;
		const float volumeDiff0 =
			aabb0.Union(node->box).Area() - aabb0.Area();
		const float volumeDiff1 =
			aabb1.Union(node->box).Area() - aabb1.Area();

		// insert to the child that gives less volume increase
		if (volumeDiff0 < volumeDiff1)
			InsertNode(node, &p->children[0]);
		else
			InsertNode(node, &p->children[1]);
	}

	// update parent AABB
	// (propagates back up the recursion stack)
	(*parent)->UpdateAABB(m_margin);
}


void DynamicTree::RemoveNode(TreeNode* node)
{
	// replace parent with sibling, remove parent node
	TreeNode* parent = node->parent;
	if (parent) // node is not root
	{
		TreeNode* sibling = node->GetSibling();
		if (parent->parent) // if there's a grandparent
		{
			// update links
			sibling->parent = parent->parent;
			(parent == parent->parent->children[0]
				? parent->parent->children[0]
				: parent->parent->children[1]) = sibling;
		}
		else // no grandparent
		{
			// make sibling root
			TreeNode* sibling = node->GetSibling();
			m_Root = sibling;
			sibling->parent = nullptr;
		}
		delete node;
		delete parent;

		UpdateNode(sibling->parent); //here!!!
	}
	else // node is root
	{
		m_Root = nullptr;
		delete node;
	}
}

void DynamicTree::ClearChildrenCrossFlagHelper(TreeNode* node)
{
	node->childrenCrossed = false;
	if (!node->IsLeaf())
	{
		ClearChildrenCrossFlagHelper(node->children[0]);
		ClearChildrenCrossFlagHelper(node->children[1]);
	}
}


void DynamicTree::ComputePairsHelper(TreeNode* n0, TreeNode* n1)
{
// 	Vector2 size0 = n0->box.upperBound - n0->box.lowerBound;
// 	Vector2 pos0 = (n0->box.lowerBound + n0->box.upperBound) / 2.f;
// 
// 	GraphicsEngine::GetInstance()->DrawRectangle(pos0, size0);
// 	Vector2 size1 = n1->box.upperBound - n1->box.lowerBound;
// 	Vector2 pos1 = (n1->box.lowerBound + n1->box.upperBound) / 2.f;
// 
// 	GraphicsEngine::GetInstance()->DrawRectangle(pos1, size1);


	if (n0->IsLeaf())
	{

		// 2 leaves, check proxies instead of fat AABBs
		if (n1->IsLeaf())
		{

			if (n0->data->GetBound().Intersects(n1->data->GetBound()))
				m_Pairs.emplace_back(n0->data,
					n1->data);
		}
		// 1 branch / 1 leaf, 2 cross checks
		else
		{

			CrossChildren(n1);
			if (!n0->box.Intersects(n1->box)) return;

			ComputePairsHelper(n0, n1->children[0]);
			ComputePairsHelper(n0, n1->children[1]);
		}
	}
	else
	{

		// 1 branch / 1 leaf, 2 cross checks
		if (n1->IsLeaf())
		{

			CrossChildren(n0);
			if (!n0->box.Intersects(n1->box)) return;

			ComputePairsHelper(n0->children[0], n1);
			ComputePairsHelper(n0->children[1], n1);
		}
		// 2 branches, 4 cross checks
		else
		{

			CrossChildren(n0);
			CrossChildren(n1);
			if (!n0->box.Intersects(n1->box)) return;

			ComputePairsHelper(n0->children[0], n1->children[0]);
			ComputePairsHelper(n0->children[0], n1->children[1]);
			ComputePairsHelper(n0->children[1], n1->children[0]);
			ComputePairsHelper(n0->children[1], n1->children[1]);
		}
	} // end of if (n0->IsLeaf())

}

void DynamicTree::CrossChildren(TreeNode* node)
{
	if (!node->childrenCrossed)
	{
		ComputePairsHelper(node->children[0], node->children[1]);
		node->childrenCrossed = true;
	}
}