#pragma once

struct Bound;

class BroadPhase
{
	
  public:
	using ColliderPair = std::pair<Collider*, Collider*>;

    // ��ε������� �� ���ο� bound�� �ִ´�.
    virtual void Add(Collider* data) abstract;
 
    // ��ε�������� bound�� �����Ѵ�.
    virtual void Remove(Collider* data) abstract;

    // bound�� ��ȭ�� ����� ������Ʈ�Ѵ�.
    virtual void Update(void) abstract;
 
    // �浹 ������ �ݶ��̴��� ����Ѵ�.
    virtual const list<ColliderPair>& ComputePairs() abstract;
     
    // Ư������ Ư�� �ݶ��̴��� ����ִ��� Ȯ���Ѵ�.
    // �׷��� ������ nullptr����
    virtual Collider *Pick(const Vector2& point) const abstract;
 
    // AABB������ ���� �ٿ��, �浹ü�� ����� ��ȯ�Ѵ�.
    virtual void Query(const Bound& bound, std::vector<Collider*>& output) const abstract;
     

};

