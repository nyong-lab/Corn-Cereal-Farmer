/// [2023/7/27] 박연하
/// --------------------------
/// 그래픽스 엔진 만들기 시작!

#pragma once

#include "../Math/Vector2.h"

#include <windows.h>
#include <wincodec.h>
#include <dwrite_3.h>
#include <dcomp.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <d2d1effects_2.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <wrl.h>
#include <stdio.h>
#include "d2dtk.h"

#include <vector>
#include <string>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid")

using Microsoft::WRL::ComPtr;
using namespace D2D1;
using namespace std;

enum class COLOR
{
	NOW,

	// CUSTOM COLOR
	TIMEBAR,
	QUESTLIST,
	EMERGENCY,
	MOON,
	SUN,
	BABYBLUE,
	SKYBLUE,
	MINT,
	APPLEGREEN,

	WHITE,
	BLACK,

	END,
};

class GraphicsEngine
{
public:
	static const Vector2 TEXTBOX_SIZE;

public:
	GraphicsEngine();
	~GraphicsEngine();

public:
	/// SINGLETON
	static GraphicsEngine* GetInstance();

	static void Destroy() { delete g_Instance; }

public:
	void Initialize(HWND hWnd);
	void Finalize();

	HRESULT CreateDeviceDependentResources();
	HRESULT CreateDeviceContext();
	void DiscardDeviceResources();

	void BeginRender();
	void EndRender();

	/// Buffer
	void DrawEffectBufferBegin();
	void DrawEffectBufferEnd();

public:
	/// COLOR
	void SetBackgroundColor(float r, float g, float b, float a);
	void SetBrushColor(UINT32 color, float alpha = 1.f);

	/// PRIMITIVE
	void DrawRectangle(Vector2 position, Vector2 size, COLOR color = COLOR::NOW, float strokeWeight = 1.f, bool isFill = false);
	void DrawEllipse(Vector2 position, Vector2 diameter, COLOR color = COLOR::NOW, float strokeWeight = 1.f, bool isFill = false);
	void DrawLine(Vector2 startPosition, Vector2 endPosition, float strokeWeight = 1.f);
	void DrawPolygon(D2D1_POINT_2F points[], const int pointsCount, COLOR color = COLOR::NOW, float strokeWeight = 1.f, bool isFill = false);

	/// TEXT
	void FontInitialize();
	void CreateCustomFont(
		IDWriteTextFormat** font,
		const wstring& fontPath,
		const wstring& fontName,
		FLOAT fontSize
	);
	void DrawText(int x, int y, const wstring& text, IDWriteTextFormat* font = nullptr, COLOR color = COLOR::NOW);

	/// TRS
	void SetTransform(const D2D1_MATRIX_3X2_F& transformMatrix);

	/// IMAGE
	HRESULT LoadBitmapFromFile(ID2D1Bitmap** image, LPCWSTR imagePath);
	void ShowImage(
		ID2D1Bitmap* image,
		Vector2 position,
		Vector2 imageSize,
		Vector2 sliceStartPosition = { 999.f, 999.f },
		Vector2 sliceSize = { 999.f, 999.f },
		D2D1_RECT_F additionalOffset = { 0.f, 0.f },
		float opacity = 1.f
	);

	/// Getter & Setter
	const D2D1_SIZE_F& GetClientSize() const { return m_DeviceContextSize; }
	ID2D1DeviceContext* GetDC() { return m_DeviceContext; }

	/// Effect
	void SetTemperatureValue(float temperatureValue) { m_TemperatureValue = temperatureValue; }
	void SetColorTintValue(float colorTintValue) { m_ColorTintValue = colorTintValue; }
	void SetWhiteCurvePoint(Vector2 whiteCurvePoint) { m_WhiteCurvePoint = whiteCurvePoint; }
	void SetBlackCurvePoint(Vector2 blackCurvePoint) { m_BlackCurvePoint = blackCurvePoint; }

	void TemperatureTintEffect(ID2D1Image* input);
	void BrightnessEffect(ID2D1Image* input);

	ID2D1Bitmap* ConvertImageToBitmap(ID2D1Image* image, D2D1_SIZE_U size);
	ID2D1Bitmap* CreateEmptyBitmap(D2D1_SIZE_U size);

private:
	/// INSTANCE
	static GraphicsEngine* g_Instance;

	/// WINDOW HANDLE
	HWND m_Hwnd;

	/// D2D
	ID2D1Factory1* m_D2DFactory;
	ID2D1HwndRenderTarget* m_RenderTarget;
	ID2D1SolidColorBrush* m_Brush[(UINT)COLOR::END];

	IWICImagingFactory* m_ImagingFactory;
	IDWriteFactory5* m_WriteFactory;
	IDWriteTextFormat* m_TextFormat;
	IDWriteFontCollection1* m_FontBox;

	HRESULT m_IsDDResReady;
	D2D1_SIZE_F m_DeviceContextSize;

	ID2D1PathGeometry* m_PathGeometry;

	/// D3D
	D3D_FEATURE_LEVEL m_FeatureLevel;
	ID2D1Device* m_D2DDevice;
	ID2D1DeviceContext* m_DeviceContext;
	IDXGISwapChain1* m_SwapChain;

	/// Buffer
	ID2D1Bitmap1* m_OriginalBuffer;

	/// Compatible Render Target
	ID2D1BitmapRenderTarget* m_CompatibleRenderTarget;

	/// 다형성용 렌더타겟
	ID2D1RenderTarget* m_PolyMorphRenderTarget;

	/// EFFECT
	ComPtr<ID2D1Effect> m_TemperatureTintEffect;
	float m_TemperatureValue;
	float m_ColorTintValue;

	ComPtr<ID2D1Effect> m_BrightnessEffect;
	Vector2 m_WhiteCurvePoint;
	Vector2 m_BlackCurvePoint;
};