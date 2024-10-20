#pragma once

struct Bound;

class BroadPhase
{
	
  public:
	using ColliderPair = std::pair<Collider*, Collider*>;

    // 브로드페이즈 시 새로운 bound를 넣는다.
    virtual void Add(Collider* data) abstract;
 
    // 브로드페이즈에서 bound를 삭제한다.
    virtual void Remove(Collider* data) abstract;

    // bound간 변화가 생기면 업데이트한다.
    virtual void Update(void) abstract;
 
    // 충돌 가능한 콜라이더를 계산한다.
    virtual const list<ColliderPair>& ComputePairs() abstract;
     
    // 특정점이 특정 콜라이더에 들어있는지 확인한다.
    // 그런거 없으면 nullptr리턴
    virtual Collider *Pick(const Vector2& point) const abstract;
 
    // AABB쿼리를 통한 바운드, 충돌체의 목록을 반환한다.
    virtual void Query(const Bound& bound, std::vector<Collider*>& output) const abstract;
     

};

