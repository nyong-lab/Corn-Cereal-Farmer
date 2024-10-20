/// 2023.07.25 
/// 작성자 : 정창도
/// 그래픽스엔진에 D3D초기화 및
/// imgui를 붙여보았다.
/// DC써가지고 여러가지 이펙트도 된다.
///
/// 2023.07.28
/// 수정 : 고윤서
/// 이미지를 불러와 저장해두는 임시 함수 만들어듐
/// tool 공부하는데 필요하다. ResourceManage빨리 주세요
/// imgui에서 image쓰기 위해 필요한 divice던지기 넣어듐
#pragma once

///image를 위한 임시 헤더
#include <string>
#include <map>


/// 이건 여기 아니면 왜 오류남?
#include <d2d1_1.h>
#include <dxgi1_2.h>
#include <d3d11.h>

/// 위에꺼친구
#include <d2d1_1helper.h>



class D2DEngine1
{
public:
	static D2DEngine1* engineInstance;

public:
	/// D2D1에 있는 ColorF함수를 래핑했다.
	static D2D1::ColorF ColorF(float red, float green, float blue, float alpha = 1.0f);

private:
	D2DEngine1();
	~D2DEngine1();
	
public:
	static D2DEngine1* GetInstance() {
		if (!engineInstance) {
			engineInstance = new D2DEngine1;
			atexit(ReleaseInstance);
		}
		return engineInstance;
	}

	static void ReleaseInstance() {
		if (engineInstance) {
			delete engineInstance;
			engineInstance = nullptr;
		}
	}

public:
	HRESULT Initialize(HWND hwnd);
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();

	/// DC 만드는 함수
	HRESULT CreateDeviceContext();

	/// D2D DeviceContext를 사용하여 그릴때 호출해야한다.
	void BeginRender();

	/// D2D DeviceContext를 사용하고 한 프레임에 다 그리면 호출해야한다.
	void EndRender();

	/// D2D DeviceContext를 사용하여 그리는 코드.
	void SelectBrush(D2D1::ColorF colorF);
	void FillRectangle(int left, int top, int right, int bottom);
	void DrawRectangle(int left, int top, int right, int bottom);
	void DrawOrientedRectangle(int left, int top, int right, int bottom, float rotation);
	void DrawLine(int startX, int StartY, int endX, int endY, float stroke);
	void DrawLine(int centerX, int CenterY, int scale, float rotation = 0);
	void FillRectangle(int left, int top, int right, int bottom, D2D1::ColorF colorF);
	void DrawRectangle(int left, int top, int right, int bottom, D2D1::ColorF colorF);
	void DrawCircle(int centerX, int centerY, int radius);

	/// 밑에는 구현중..
	void PrintText();
	template <typename T>
	void PrintText();
	template <typename T, typename... args>
	void PrintText();

	/// 점 주면 그 점들 이어서 폴리곤을 그린다.
	void DrawPolygon(D2D1_POINT_2F points[], const int pointsCount);

	/// 셋트랜스폼 래핑 wrapping
	void SetTransform(D2D1::Matrix3x2F matrix3x2F);
	
	/// 배경색칠하기
	void Clear(D2D1::ColorF colorF);

	
	/// 이미지 그리는 임시 함수들
	HRESULT CreateD2DBitmapFromFile(const std::wstring& imageName, const LPCWSTR& imagePath);
	ID2D1Bitmap* getImage(const std::wstring& imageName);
	ID2D1Bitmap* findImage(const std::wstring& imageName);
	bool DrawBitMaps(ID2D1Bitmap* bitMap);

	std::map<std::wstring, ID2D1Bitmap*> images;

	/// imgui 함수
	// Forward declarations of helper functions
	// bool CreateDeviceD3D(HWND hWnd);


	void CreateRenderTarget();
	void CleanupRenderTarget();
	
	

private:
 	HWND m_Hwnd;


	/// ID2D1Factory 에서 ID2D1Factory1로 업그레이드.. dc를 위해..
 	ID2D1Factory1* m_D2DFactory;
 	ID2D1HwndRenderTarget* m_RenderTarget;
	ID2D1SolidColorBrush* m_BlackBrush;
	ID2D1SolidColorBrush* m_SelectedBrush;
	ID2D1SolidColorBrush* m_TempBrush;

	ID2D1PathGeometry* m_PathGeometry;
	IWICImagingFactory* m_WICFactory;	// Windows Imaging Component ms 제공 이미지 처리 및 코덱 라이브러리 

	IDWriteFactory* m_DWriteFactory;	// 글자쓰는 텍스트 포멧같은거 만들어주는 팩토리
	IDWriteTextFormat* m_TextFormat;	// 텍스트 포맷!

	IWICImagingFactory* g_pIWICImagingFactory = NULL; //이미지 팩토리

	/// 밑에서부터 D3D붙이기
	D3D_FEATURE_LEVEL m_FeatureLevel;
	ID2D1Device* m_D2DDevice;
	ID2D1DeviceContext* m_DeviceContext;
	IDXGISwapChain1* m_SwapChain;
	ID2D1Bitmap1* m_D2DTargetBitmap;

	float m_dpi;


	/// imgui
	ID3D11Device* m_D3DDevice;
	ID3D11DeviceContext* m_D3DDeviceContext;
	ID3D11RenderTargetView* m_MainRenderTargetView;
	UINT m_ResizeWidth, m_ResizeHeight;
	
	
public:
	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
	
};
