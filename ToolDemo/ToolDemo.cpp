#include "pch.h"

#include "ToolDemo.h"
#include "../D2Dimgui/D2DEngine1.h"
#include "../D2Dimgui/imgui.h"

#include "../Math/Vector2.h"


#include "Object.h"
#include "MyRectangle.h"
#include "MyHeart.h"

//image
#define STB_IMAGE_IMPLEMENTATION

///임시 전역변수들
float xPos = 100;
float yPos = 100;

/// 임시 그래픽스엔진 
D2DEngine1* m_D2DEngine;
HWND m_hWnd;

// 윈도 프로시저
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	// 지정된 힙에 대한 기능을 사용하도록 설정합니다.
	// 손상에 대한 종료 기능을 사용하도록 설정합니다. 힙 관리자가 프로세스에서 사용하는 모든 힙에서 오류를 감지하면 Windows 오류 보고 서비스를 호출하고 프로세스를 종료합니다. 
	// by msdn
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);


	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(1555);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			ToolDemo toolDemo;

			WNDCLASSEXW wcex;

			wcex.cbSize = sizeof(WNDCLASSEX);

			wcex.style = CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc = WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = hInstance;
			wcex.hIcon = nullptr;
			wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcex.hbrBackground = nullptr;
			wcex.lpszMenuName = nullptr;
			wcex.lpszClassName = L"ZICOEngineDemo";
			wcex.hIconSm = nullptr;

			RegisterClassExW(&wcex);

			m_hWnd = CreateWindowW(
				L"ZICOEngineDemo",
				L"ZICO EngineDemo V2",
				WS_OVERLAPPEDWINDOW, 100, 100, 1800, 1000, nullptr, nullptr, hInstance, nullptr);



			ShowWindow(m_hWnd, SW_SHOWNORMAL);
			UpdateWindow(m_hWnd);



			/// 게임엔진 초기화는 이 밑에서 한다.
			m_D2DEngine = D2DEngine1::GetInstance();
			m_D2DEngine->Initialize(m_hWnd);

			///IMGUI
			D2DEngine1::GetInstance()->CreateD2DBitmapFromFile(L"apple", L".\\Resources\\Image\\ImGUI\\apple.png");
			D2DEngine1::GetInstance()->CreateD2DBitmapFromFile(L"heart", L".\\Resources\\Image\\ImGUI\\heart.png");
			D2DEngine1::GetInstance()->CreateD2DBitmapFromFile(L"man", L".\\Resources\\Image\\ImGUI\\man.png");
			D2DEngine1::GetInstance()->CreateD2DBitmapFromFile(L"moon", L".\\Resources\\Image\\ImGUI\\moon.png");

			toolDemo.RunMessageLoop();


			toolDemo.Finalize();
		}
		CoUninitialize();
	}


	return 0;
}

ToolDemo::ToolDemo()
	: rectangleID(0)
{
	///기본적인 초기화작업?
	m_ObjectList.clear();

}

ToolDemo::~ToolDemo()
{

}

void ToolDemo::Finalize()
{
	D2DEngine1::ReleaseInstance();
}

#include "../D2Dimgui/imgui_impl_win32.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message)
	{

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void ToolDemo::RunMessageLoop()
{
	MSG msg;

	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			Update();
			Render();
		}
	}
}

void ToolDemo::Update()
{
	for (auto _list : m_ObjectList)
	{
		_list->Update();
	}
}


///임시 컬러
D2D1::ColorF g_Color(0.1f, 0.2f, 0.3f);
int clickCheck = 0;
void ToolDemo::Render()
{

	///d2d
	D2DEngine1::GetInstance()->BeginRender();


	D2DEngine1::GetInstance()->Clear(g_Color);

	bool show_demo_window = true;
	bool show_another_window = false;
	bool show_my_window = true;
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.WantCaptureMouse = true; //마우스 입력을 받을 수 있게 해줌 

	//D2DEngine1::GetInstance()->PrintText();

	ImVec2 mousePos = io.MousePos;


	for (auto _list : m_ObjectList)
	{
		if (AABBCheck(_list->GetPosition().x, _list->GetPosition().x + _list->GetSize().x, _list->GetPosition().y, _list->GetPosition().y + _list->GetSize().y, mousePos.x, mousePos.x + 10, mousePos.y, mousePos.y + 10) == true)
		{
			_list->SetCollision(true);
		}
		else
			_list->SetCollision(false);
	}

	for (auto _list : m_ObjectList)
	{
		_list->Render(m_D2DEngine);
		if (_list->GetCollision() == true)
			if (ImGui::IsMouseDragging(0))
			{
				_list->Move(Vector2(mousePos.x, mousePos.y));
			}
	}



	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	///내가 원하는 대로 만들어보기
	//if (show_my_window)
	{
		ImGui::Begin("New Window", NULL, ImGuiWindowFlags_MenuBar);

		///MenuBar
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
				clickCheck++;
			if (ImGui::MenuItem("Open"))
				clickCheck++;
			ImGui::EndMenu();
		}
		//ImGui::EndMenuBar();

		ImGui::Text("Is it works? %d", clickCheck);


		///button
		{
			ImGui::Text("Button");
			ImGui::SameLine(100.0f, 0.0f);
			////기본 버튼 색
			//ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::ImColor(30.0f, 30.0f, 30.0f));
			////마우스가 올라갔을 때 버튼 색
			//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::ImColor(80.0f, 80.0f, 30.0f));
			////클릭했을 때 버튼 색
			//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::ImColor(9.0f, 21.0f, 33.0f));
			//근데 기본 버튼이 보기 젤 좋은건 안비밀

			ImGui::Button("Button");
			//ImGui::PopStyleColor(3);
		}

		

		ID3D11ShaderResourceView* my_texture2 = NULL;
		int my_image_width2 = 0;
		int my_image_height2 = 0;
		D2DEngine1::GetInstance()->LoadTextureFromFile("..\\Resources\\Image\\ImGUI\\heart.png", &my_texture2, &my_image_width2, &my_image_height2);
		/*ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));*/
		
		///ImageButton 근데 안먹음
		{
			if (ImGui::ImageButton(my_texture2, ImVec2(my_image_width2, my_image_height2)))
			{
				Object* newHeart = new MyHeart(heartID, "Heart", Vector2(50, 50), Vector2(300, 300));
				heartID++;
				m_ObjectList.push_back(newHeart);
			}
			//ImGui::ImageButton(myTextID, ImVec2(400, 360), ImVec2(0.0f, 0.0f));
			//ImGui::PopStyleColor(3);
		}

		/// 마우스 연동 연습
		ImGui::Text("X : %.1f Y : %.1f", xPos, yPos);

		///Create Rectangle button
		{
			ImGui::Text("Create New Rectangle");
			ImGui::SameLine(200.0f, 0.0f);
			if (ImGui::Button("Create"))
			{
				Object* newRectangle = new MyRectangle(rectangleID, "Rectangle", Vector2(100, 100), Vector2(200, 200));
				rectangleID++;
				m_ObjectList.push_back(newRectangle);
				OutputDebugString(TEXT("Check"));

				
			}

			//ImGui::PopStyleColor(3);
		}

		///listBox
		{
			int current_part_idx = 0;

			// Draw list
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
			const auto child_size = ImVec2(400, 280);
			ImGui::BeginChild("ChildDrawList", child_size, true, ImGuiWindowFlags_MenuBar);

			// ImGui::ChildWindowHeader(tr("Draw list"));
			if (ImGui::BeginMenuBar())
			{
				//ImGui::TextUnformatted((L"Draw list").c_str());
				ImGui::EndMenuBar();
			}
			const auto  draw_list_size = ImVec2(400, 260);
			const char* items[] = { "AAAA",    "BBBB", "CCCC", "DDDD",  "EEEE", "FFFF",  "GGGG",  "HHHH", "IIII",   "JJJJ", "KKKK",
								   "LLLLLLL", "MMMM", "NNNN", "OOOOO", "PPP",  "QQQQQ", "RRRRR", "SSSS", "TTTTTT", "UUU" };
			if (ImGui::BeginListBox("##draw_list", draw_list_size))
			{
				if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_DownArrow)))
				{
					if (current_part_idx < 20) { ++current_part_idx; }
				}
				if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_UpArrow)))
				{
					if (current_part_idx > 0) { --current_part_idx; }
				}

				for (int n = 0; n < IM_ARRAYSIZE(items); ++n)
				{
					const bool is_selected = (current_part_idx == n);
					if (ImGui::Selectable(items[n], is_selected)) { current_part_idx = n; }

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected) { ImGui::SetItemDefaultFocus(); }
				}
				ImGui::EndListBox();

				ImGui::EndChild();
				ImGui::PopStyleVar();
			}

			ImGui::End();
		}

		///이미지 확인
		ID3D11ShaderResourceView* my_texture = NULL;
		int my_image_width = 0;
		int my_image_height = 0;
		D2DEngine1::GetInstance()->LoadTextureFromFile("..\\Resources\\Image\\ImGUI\\apple.png", &my_texture, &my_image_width, &my_image_height);
		{
			ImGui::Begin("DirectX11 Texture Test");
			ImGui::Text("pointer = %p", my_texture);
			ImGui::Text("size = %d x %d", my_image_width, my_image_height);
			ImGui::Image((void*)my_texture, ImVec2(my_image_width, my_image_height));
			ImGui::End();
		}
		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&g_Color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImVec2 mousePos = io.MousePos;
			ImGui::Text("counter = %f, %f", mousePos.x, mousePos.y);

			bool mouseClick = io.MouseClicked;
			ImGui::Text("click = %d", mouseClick);



			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}



		D2DEngine1::GetInstance()->EndRender();
	}
}

bool ToolDemo::AABBCheck(float rect1X, float rect1Width, float rect1Y, float rect1Height, float rect2X, float rect2Width, float rect2Y, float rect2Height)
{
	int checkX = 0;
	int checkY = 0;

	if ((rect1X <= rect2X && rect1Width >= rect2X) || (rect1X <= rect2Width && rect1Width >= rect2Width))
		checkX = 1;
	else
		checkX = 0;

	if ((rect1Y <= rect2Y && rect1Height >= rect2Y) || (rect1Y <= rect2Height && rect1Height >= rect2Height))
		checkY = 1;
	else
		checkY = 0;

	if (checkX == 1 && checkY == 1) // 충돌시
		return true;
	else
		return false;
}

void ToolDemo::createNewRectangle()
{

}



