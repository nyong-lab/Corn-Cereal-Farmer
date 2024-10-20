#include "MyRectangle.h"

MyRectangle::MyRectangle(int id, std::string name, Vector2 position, Vector2 size)
	: Object(id, name, position, size)
{

}

MyRectangle::~MyRectangle()
{

}

void MyRectangle::Move(Vector2 vec)
{
	 m_Position.x =  vec.x;
	 m_Position.y = vec.y;
}

void MyRectangle::Render(D2DEngine1* d2dEngine)
{
	int width = 0;
	int height = 0;
	m_WindowID = std::to_string(m_ID) + m_Name;
	d2dEngine->GetInstance()->LoadTextureFromFile("..\\Resources\\Image\\ImGUI\\moon.png", &m_Texture, &width, &height);
	ImGui::Begin(m_WindowID.c_str());
	ImGui::Text("pointer = %p", m_Texture);
	ImGui::Text("size = %d x %d", width, height);
	ImGui::Image((void*)m_Texture, ImVec2(width, height));
	ImGui::End();
	
	//d2dEngine->GetInstance()->DrawRectangle(m_Position.x, m_Position.y, m_Size.x + m_Position.x, m_Size.y + m_Position.y);
}

void MyRectangle::Update()
{
	
}
