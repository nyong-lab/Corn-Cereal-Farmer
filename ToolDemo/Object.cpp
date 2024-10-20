#include "Object.h"


Object::Object(int id, std::string name, Vector2 position, Vector2 size)
	: m_ID(id)
	, m_Name(name)
	, m_Position(position)
	, m_Size(size)
{

}

Object::~Object()
{

}
