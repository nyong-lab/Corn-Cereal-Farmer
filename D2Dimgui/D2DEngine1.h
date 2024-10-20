/// 2023.07.25 
/// �ۼ��� : ��â��
/// �׷��Ƚ������� D3D�ʱ�ȭ ��
/// imgui�� �ٿ����Ҵ�.
/// DC�ᰡ���� �������� ����Ʈ�� �ȴ�.
///
/// 2023.07.28
/// ���� : ������
/// �̹����� �ҷ��� �����صδ� �ӽ� �Լ� ������
/// tool �����ϴµ� �ʿ��ϴ�. ResourceManage���� �ּ���
/// imgui���� image���� ���� �ʿ��� divice������ �־��
#pragma once

///image�� ���� �ӽ� ���
#include <string>
#include <map>


/// �̰� ���� �ƴϸ� �� ������?
#include <d2d1_1.h>
#include <dxgi1_2.h>
#include <d3d11.h>

/// ������ģ��
#include <d2d1_1helper.h>



class D2DEngine1
{
public:
	static D2DEngine1* engineInstance;

public:
	/// D2D1�� �ִ� ColorF�Լ��� �����ߴ�.
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

	/// DC ����� �Լ�
	HRESULT CreateDeviceContext();

	/// D2D DeviceContext�� ����Ͽ� �׸��� ȣ���ؾ��Ѵ�.
	void BeginRender();

	/// D2D DeviceContext�� ����ϰ� �� �����ӿ� �� �׸��� ȣ���ؾ��Ѵ�.
	void EndRender();

	/// D2D DeviceContext�� ����Ͽ� �׸��� �ڵ�.
	void SelectBrush(D2D1::ColorF colorF);
	void FillRectangle(int left, int top, int right, int bottom);
	void DrawRectangle(int left, int top, int right, int bottom);
	void DrawOrientedRectangle(int left, int top, int right, int bottom, float rotation);
	void DrawLine(int startX, int StartY, int endX, int endY, float stroke);
	void DrawLine(int centerX, int CenterY, int scale, float rotation = 0);
	void FillRectangle(int left, int top, int right, int bottom, D2D1::ColorF colorF);
	void DrawRectangle(int left, int top, int right, int bottom, D2D1::ColorF colorF);
	void DrawCircle(int centerX, int centerY, int radius);

	/// �ؿ��� ������..
	void PrintText();
	template <typename T>
	void PrintText();
	template <typename T, typename... args>
	void PrintText();

	/// �� �ָ� �� ���� �̾ �������� �׸���.
	void DrawPolygon(D2D1_POINT_2F points[], const int pointsCount);

	/// ��Ʈ������ ���� wrapping
	void SetTransform(D2D1::Matrix3x2F matrix3x2F);
	
	/// ����ĥ�ϱ�
	void Clear(D2D1::ColorF colorF);

	
	/// �̹��� �׸��� �ӽ� �Լ���
	HRESULT CreateD2DBitmapFromFile(const std::wstring& imageName, const LPCWSTR& imagePath);
	ID2D1Bitmap* getImage(const std::wstring& imageName);
	ID2D1Bitmap* findImage(const std::wstring& imageName);
	bool DrawBitMaps(ID2D1Bitmap* bitMap);

	std::map<std::wstring, ID2D1Bitmap*> images;

	/// imgui �Լ�
	// Forward declarations of helper functions
	// bool CreateDeviceD3D(HWND hWnd);


	void CreateRenderTarget();
	void CleanupRenderTarget();
	
	

private:
 	HWND m_Hwnd;


	/// ID2D1Factory ���� ID2D1Factory1�� ���׷��̵�.. dc�� ����..
 	ID2D1Factory1* m_D2DFactory;
 	ID2D1HwndRenderTarget* m_RenderTarget;
	ID2D1SolidColorBrush* m_BlackBrush;
	ID2D1SolidColorBrush* m_SelectedBrush;
	ID2D1SolidColorBrush* m_TempBrush;

	ID2D1PathGeometry* m_PathGeometry;
	IWICImagingFactory* m_WICFactory;	// Windows Imaging Component ms ���� �̹��� ó�� �� �ڵ� ���̺귯�� 

	IDWriteFactory* m_DWriteFactory;	// ���ھ��� �ؽ�Ʈ ���䰰���� ������ִ� ���丮
	IDWriteTextFormat* m_TextFormat;	// �ؽ�Ʈ ����!

	IWICImagingFactory* g_pIWICImagingFactory = NULL; //�̹��� ���丮

	/// �ؿ������� D3D���̱�
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
