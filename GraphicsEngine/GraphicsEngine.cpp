#include "GraphicsEngine.h"
#include "macro.h"

/// ===================
///		INITIALIZE
/// ===================

GraphicsEngine* GraphicsEngine::g_Instance = nullptr;

const Vector2 GraphicsEngine::TEXTBOX_SIZE = { 500.f, 40.f };

GraphicsEngine::GraphicsEngine()
	: m_Hwnd(nullptr)
	, m_D2DFactory(nullptr)
	, m_RenderTarget(nullptr)
	, m_CompatibleRenderTarget(nullptr)
	, m_OriginalBuffer(nullptr)
	, m_PolyMorphRenderTarget(nullptr)
	, m_Brush{}
	, m_ImagingFactory(nullptr)
	, m_WriteFactory(nullptr)
	, m_TextFormat(nullptr)
	, m_FontBox(nullptr)
	, m_IsDDResReady()
	, m_DeviceContextSize()
	, m_FeatureLevel()
	, m_D2DDevice(nullptr)
	, m_DeviceContext(nullptr)
	, m_SwapChain(nullptr)
	, m_PathGeometry(nullptr)
	, m_TemperatureValue(0.f)
	, m_ColorTintValue(0.f)
	, m_WhiteCurvePoint{}
	, m_BlackCurvePoint{}
{
	g_Instance = this;
}

GraphicsEngine::~GraphicsEngine()
{

}

GraphicsEngine* GraphicsEngine::GetInstance()
{
	if (g_Instance == NULL)
		g_Instance = new GraphicsEngine();
	return g_Instance;
}

void GraphicsEngine::Initialize(HWND hWnd)
{
	m_Hwnd = hWnd;

	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&m_D2DFactory
	);

	// WIC Imaging Factory 생성
	HRESULT hResult = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_ImagingFactory)
		);
	}

	// Write Factory 생성
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory5),
			reinterpret_cast<IUnknown**>(&m_WriteFactory)
		);
	}

	// Font Initialize
	FontInitialize();

	// Device Dependent Resources 생성
	m_IsDDResReady = CreateDeviceDependentResources();

	// Effect
	m_DeviceContext->CreateEffect(CLSID_D2D1TemperatureTint, &m_TemperatureTintEffect);
	m_DeviceContext->CreateEffect(CLSID_D2D1Brightness, &m_BrightnessEffect);
}

void GraphicsEngine::Finalize()
{
	DiscardDeviceResources();
}

HRESULT GraphicsEngine::CreateDeviceDependentResources()
{
	RECT rc;
	GetClientRect(m_Hwnd, &rc);
	D2D1_SIZE_U size = SizeU(rc.right - rc.left, rc.bottom - rc.top);

	HRESULT hr = S_OK;
	if (m_DeviceContext == nullptr)
	{
		// Device Context 생성
		CreateDeviceContext();

		hr = m_D2DFactory->CreateHwndRenderTarget(
			RenderTargetProperties(),
			HwndRenderTargetProperties(m_Hwnd, size),
			&m_RenderTarget);

		if (SUCCEEDED(hr))
		{
			hr = m_DeviceContext->CreateSolidColorBrush(ColorF(0xFFFFFF), &m_Brush[(UINT)COLOR::NOW]);
			hr = m_DeviceContext->CreateSolidColorBrush(ColorF(0x692B09), &m_Brush[(UINT)COLOR::TIMEBAR]);
			hr = m_DeviceContext->CreateSolidColorBrush(ColorF(0x313359), &m_Brush[(UINT)COLOR::QUESTLIST]);
			hr = m_DeviceContext->CreateSolidColorBrush(ColorF(0xB51A1A), &m_Brush[(UINT)COLOR::EMERGENCY]);
			hr = m_DeviceContext->CreateSolidColorBrush(ColorF(0xB1B4F0), &m_Brush[(UINT)COLOR::MOON]);
			hr = m_DeviceContext->CreateSolidColorBrush(ColorF(0xFFD467), &m_Brush[(UINT)COLOR::SUN]);
			hr = m_DeviceContext->CreateSolidColorBrush(ColorF(0xA3C4F3), &m_Brush[(UINT)COLOR::BABYBLUE]);
			hr = m_DeviceContext->CreateSolidColorBrush(ColorF(0x90DBF4), &m_Brush[(UINT)COLOR::SKYBLUE]);
			hr = m_DeviceContext->CreateSolidColorBrush(ColorF(0x98F5E1), &m_Brush[(UINT)COLOR::MINT]);
			hr = m_DeviceContext->CreateSolidColorBrush(ColorF(0xB9FBC0), &m_Brush[(UINT)COLOR::APPLEGREEN]);
			hr = m_DeviceContext->CreateSolidColorBrush(ColorF(0xFFFFFF), &m_Brush[(UINT)COLOR::WHITE]);
			hr = m_DeviceContext->CreateSolidColorBrush(ColorF(0x000000), &m_Brush[(UINT)COLOR::BLACK]);
		}
	}

	return hr;
}

HRESULT GraphicsEngine::CreateDeviceContext()
{
	// API 기본값과 다른 색상 채널 순서를 지원하기 위한 플래그입니다.
	// Direct2D와의 호환성을 위해 필요합니다.
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	// 이 배열은 이 앱이 지원하는 DirectX 하드웨어 기능 레벨을 정의합니다.
	// 순서가 중요하며 꼭 유지해야 합니다.
	// 앱의 최소 요구 기능 레벨을 설명에 선언하는 것을 잊지 마세요.
	// 모든 앱은 그렇지 않은 한 9.1을 지원하는 것으로 가정됩니다.
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	// DX11 API 장치 개체를 만들고 해당 컨텍스트를 가져옵니다.
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	DX::ThrowIfFailed(
		D3D11CreateDevice(
			nullptr,                    // 기본 어댑터 사용을 위해 null 지정
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			creationFlags,              // 디버그 및 Direct2D 호환성 플래그 선택적으로 설정
			featureLevels,              // 이 앱이 지원할 수 있는 기능 레벨 목록
			ARRAYSIZE(featureLevels),   // 가능한 기능 레벨의 수
			D3D11_SDK_VERSION,
			&device,                    // 생성된 Direct3D 장치 반환
			&m_FeatureLevel,		    // 생성된 장치의 기능 레벨 반환
			&context                    // 장치의 즉시 컨텍스트 반환
		)
	);

	
	ComPtr<IDXGIDevice1> dxgiDevice;

	// Direct3D11 장치의 기본 DXGI 장치를 가져옵니다.
	DX::ThrowIfFailed(
		device.As(&dxgiDevice)
	);

	// 2D 렌더링을 위한 Direct2D 장치를 가져옵니다.
	DX::ThrowIfFailed(
		m_D2DFactory->CreateDevice(dxgiDevice.Get(), &m_D2DDevice)
	);

	// Direct2D 장치에 해당하는 장치 컨텍스트 개체를 가져옵니다.
	DX::ThrowIfFailed(
		m_D2DDevice->CreateDeviceContext(
			D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&m_DeviceContext
		)
	);

	

	// 디스크립터 할당.
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Width = 0;										// 자동 크기 조정 사용
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// 가장 일반적인 스왑 체인 포맷
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;								// 멀티샘플링 사용하지 않음
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;									// 더블 버퍼링 사용하여 플립 가능하게 함
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	// 모든 앱은 이 SwapEffect를 사용해야 함
	swapChainDesc.Flags = 0;

	// 이 장치가 실행되는 물리적 어댑터(GPU 또는 카드)를 식별.
	ComPtr<IDXGIAdapter> dxgiAdapter;
	DX::ThrowIfFailed(
		dxgiDevice->GetAdapter(&dxgiAdapter)
	);

	// 이 DXGI 장치를 만든 팩토리 개체 가져오기.
	ComPtr<IDXGIFactory2> dxgiFactory;
	DX::ThrowIfFailed(
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
	);

	// DXGI 팩토리에서 이 윈도우에 대한 최종 스왑 체인 가져오기.
// 	DX::ThrowIfFailed(
// 		dxgiFactory->CreateSwapChainForCoreWindow(
// 			device.Get(),
// 			reinterpret_cast<IUnknown*>(m_Hwnd),
// 			&swapChainDesc,
// 			nullptr,    // 모든 디스플레이에서 허용
// 			&m_SwapChain
// 		)
// 	);

	DXGI_RATIONAL rate{};
	rate.Denominator = 60;
	rate.Numerator = 1;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainDescFull{};
	swapChainDescFull.RefreshRate = rate;
	swapChainDescFull.Scaling = DXGI_MODE_SCALING_STRETCHED;
	swapChainDescFull.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST;
	swapChainDescFull.Windowed = true;

	dxgiFactory->CreateSwapChainForHwnd(
		device.Get(),
		m_Hwnd,
		&swapChainDesc,
		&swapChainDescFull, // 전체화면 스왑체인 설정
		nullptr,
		&m_SwapChain);

	// DXGI가 동시에 하나 이상의 프레임을 대기하지 않도록 보장.
	DX::ThrowIfFailed(
		dxgiDevice->SetMaximumFrameLatency(1)
	);

	// 이 윈도우에 대한 백버퍼를 가져와서 최종 3D 렌더링 대상으로 사용.
	ComPtr<ID3D11Texture2D> backBuffer;
	DX::ThrowIfFailed(
		m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))
	);

	// DPI를 가져온다
	float dpi;
	dpi = (float)GetDpiForWindow(m_Hwnd);

	// 이제 스왑 체인과 연결된 Direct2D 렌더 타겟 비트맵을 설정.
	// 이 비트맵에 렌더링할 때마다 윈도우와 연결된 스왑 체인에 직접 렌더링됩니다.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			dpi,
			dpi
		);

	// Direct2D가 백버퍼 서피스 포인터의 DXGI 버전을 필요로 합니다.
	ComPtr<IDXGISurface> dxgiBackBuffer;
	DX::ThrowIfFailed(
		m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer))
	);

	// DXGI 백버퍼에서 D2D 렌더 타겟으로 사용할 D2D 서피스 가져오기.
	DX::ThrowIfFailed(
		m_DeviceContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer.Get(),
			&bitmapProperties,
			&m_OriginalBuffer
		)
	);

	// 이제 Direct2D 렌더 타겟을 설정.
	m_DeviceContext->SetTarget(m_OriginalBuffer);

	/// 여기서부터 중간비트맵 만들기
	/// 현재 렌더링 대상 과 호환되는 중간 오프스크린 그리기 중에 사용할 새 비트맵 렌더링 대상을 만듭니다.
	if (!m_DeviceContext) return S_FALSE;
	HRESULT hr = m_DeviceContext->CreateCompatibleRenderTarget(
		m_DeviceContext->GetSize(),
		&m_CompatibleRenderTarget
	);

	m_PolyMorphRenderTarget = m_DeviceContext;


	/// 여기까지

	return S_OK;
}

void GraphicsEngine::DiscardDeviceResources()
{
	// COM 인터페이스 해제
	SafeRelease(&m_D2DFactory);
	SafeRelease(&m_RenderTarget);
	SafeRelease(&m_ImagingFactory);
	SafeRelease(&m_WriteFactory);
	SafeRelease(&m_TextFormat);
	SafeRelease(&m_FontBox);
	SafeRelease(&m_PathGeometry);
	SafeRelease(&m_D2DDevice);
	SafeRelease(&m_DeviceContext);
	SafeRelease(&m_SwapChain);
	SafeRelease(&m_OriginalBuffer);
	SafeRelease(&m_CompatibleRenderTarget);

	for (auto& brush : m_Brush)
	{
		SafeRelease(&brush);
	}

	CoUninitialize();
}

void GraphicsEngine::BeginRender()
{
	m_IsDDResReady = CreateDeviceDependentResources();

	if (SUCCEEDED(m_IsDDResReady) && !(m_RenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		m_DeviceContextSize = m_DeviceContext->GetSize();

		m_DeviceContext->BeginDraw();
		m_DeviceContext->SetTransform(Matrix3x2F::Identity());
		m_DeviceContext->Clear(ColorF(ColorF::Black));
	}
}

void GraphicsEngine::EndRender()
{
	if (SUCCEEDED(m_IsDDResReady) && !(m_RenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		HRESULT hr = m_DeviceContext->EndDraw();

		DXGI_PRESENT_PARAMETERS parameters{};
		parameters.DirtyRectsCount = 0;			// 0이면 전체 프레임 업데이트
		parameters.pDirtyRects = nullptr;		// DirtyRectsCount가 0이면 NULL로 설정 가능
		parameters.pScrollRect = nullptr;		// NULL이면 콘텐츠가 이전 프레임에서 스크롤되지 않음
		parameters.pScrollOffset = nullptr;		// NULL이면 오프셋 없음

		DX::ThrowIfFailed(
			m_SwapChain->Present1(1, 0, &parameters)
		);

		// 자원을 복구해야 할 경우
		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResources();
		}
	}
}

/// ===================
///		  BUFFER
/// ===================

void GraphicsEngine::DrawEffectBufferBegin()
{
	m_PolyMorphRenderTarget = m_CompatibleRenderTarget;

	m_CompatibleRenderTarget->BeginDraw();
	m_CompatibleRenderTarget->Clear(ColorF(ColorF::Black));
	m_CompatibleRenderTarget->SetTransform(Matrix3x2F::Identity());
}

void GraphicsEngine::DrawEffectBufferEnd()
{
	m_CompatibleRenderTarget->EndDraw();
	
	ID2D1Bitmap* pTemp = nullptr;

	m_CompatibleRenderTarget->GetBitmap(&pTemp);

	m_PolyMorphRenderTarget = m_DeviceContext;

	TemperatureTintEffect(pTemp);
	m_DeviceContext->DrawImage(m_TemperatureTintEffect.Get());

	ID2D1Image* image = nullptr;
	m_TemperatureTintEffect->GetOutput(&image);

	BrightnessEffect(image);
	m_DeviceContext->DrawImage(m_BrightnessEffect.Get());
}

/// ===================
///		   COLOR
/// ===================

void GraphicsEngine::SetBackgroundColor(float r, float g, float b, float a)
{
	D2D1_COLOR_F backgroundColor = ColorF(r, g, b, a);
	m_PolyMorphRenderTarget->Clear(backgroundColor);
}

void GraphicsEngine::SetBrushColor(UINT32 color, float alpha)
{
	SafeRelease(&m_Brush[(UINT)COLOR::NOW]);
	m_PolyMorphRenderTarget->CreateSolidColorBrush(ColorF(color, alpha), &m_Brush[(UINT)COLOR::NOW]);
}

/// ===================
///		 PRIMITIVE
/// ===================

void GraphicsEngine::DrawRectangle(Vector2 position, Vector2 size, COLOR color, float strokeWeight, bool isFill)
{
	D2D1_RECT_F rt = {};
	rt.left = position.x - size.x / 2;
	rt.top = position.y - size.y / 2;
	rt.right = position.x + size.x / 2;
	rt.bottom = position.y + size.y / 2;

	if (isFill) m_PolyMorphRenderTarget->FillRectangle(rt, m_Brush[(UINT)color]);
	else m_PolyMorphRenderTarget->DrawRectangle(rt, m_Brush[(UINT)color], strokeWeight);
}

void GraphicsEngine::DrawEllipse(Vector2 position, Vector2 diameter, COLOR color, float strokeWeight, bool isFill)
{
	D2D1_ELLIPSE el = {};
	el.point = Point2F(position.x, position.y);
	el.radiusX = diameter.x;
	el.radiusY = diameter.y;

	if (isFill) m_PolyMorphRenderTarget->FillEllipse(el, m_Brush[(UINT)color]);
	else m_PolyMorphRenderTarget->DrawEllipse(el, m_Brush[(UINT)color], strokeWeight);
}

void GraphicsEngine::DrawLine(Vector2 startPosition, Vector2 endPosition, float strokeWeight)
{
	m_PolyMorphRenderTarget->DrawLine(
		Point2F(startPosition.x, startPosition.y),
		Point2F(endPosition.x, endPosition.y),
		m_Brush[(UINT)COLOR::NOW],
		strokeWeight);
}

void GraphicsEngine::DrawPolygon(D2D1_POINT_2F points[], const int pointsCount, COLOR color, float strokeWeight, bool isFill)
{
	HRESULT hr = m_D2DFactory->CreatePathGeometry(&m_PathGeometry);
	if (SUCCEEDED(hr))
	{
		ID2D1GeometrySink* pSink = NULL;

		hr = m_PathGeometry->Open(&pSink);
		if (SUCCEEDED(hr))
		{
			pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

			pSink->BeginFigure(
				points[0],
				D2D1_FIGURE_BEGIN_FILLED
			);

			pSink->AddLines(points, pointsCount);
			pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		}
		hr = pSink->Close();

		if (isFill) m_PolyMorphRenderTarget->FillGeometry(m_PathGeometry, m_Brush[(UINT)color]);
		else m_PolyMorphRenderTarget->DrawGeometry(m_PathGeometry, m_Brush[(UINT)color], strokeWeight);

		SafeRelease(&pSink);
		SafeRelease(&m_PathGeometry);
	}
}


/// ===================
///		   TEXT
/// ===================

void GraphicsEngine::FontInitialize()
{
	LPCSTR path = "굴림";
	int font = AddFontResourceA(path);
	SendMessageA(HWND_BROADCAST, WM_FONTCHANGE, NULL, NULL);

	LPCWSTR fontName = L"굴림";
	const FLOAT fontSize = 12;

	HRESULT hr =
		m_WriteFactory->CreateTextFormat(
			fontName,
			NULL,								// use system font collection
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,
			L"",
			&m_TextFormat);

	if (SUCCEEDED(hr))
	{
		m_TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}
}

void GraphicsEngine::CreateCustomFont(
	IDWriteTextFormat** font,
	const wstring& fontPath,
	const wstring& fontName,
	FLOAT fontSize)
{
	if (m_WriteFactory == nullptr) return;
	HRESULT hr = S_OK;

	IDWriteFontSetBuilder1* fontSetBuilder = nullptr;
	if (SUCCEEDED(hr))
	{
		hr = m_WriteFactory->CreateFontSetBuilder(&fontSetBuilder);
	}

	IDWriteFontFile* fontFile = nullptr;
	if (SUCCEEDED(hr))
	{
		hr = m_WriteFactory->CreateFontFileReference(fontPath.c_str(), nullptr, &fontFile);
	}

	if (SUCCEEDED(hr))
	{
		hr = fontSetBuilder->AddFontFile(fontFile);
	}

	IDWriteFontSet* fontSet = nullptr;
	if (SUCCEEDED(hr))
	{
		hr = fontSetBuilder->CreateFontSet(&fontSet);
	}

	if (SUCCEEDED(hr))
	{
		m_WriteFactory->CreateFontCollectionFromFontSet(fontSet, &m_FontBox);
	}

	hr = m_WriteFactory->CreateTextFormat(
		fontName.c_str(),
		m_FontBox,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"Ko-KR",
		font
	);

	SafeRelease(&fontSetBuilder);
	SafeRelease(&fontFile);
	SafeRelease(&fontSet);
}

void GraphicsEngine::DrawText(int x, int y, const wstring& text, IDWriteTextFormat* font, COLOR color)
{
	if (font == nullptr)
	{
		font = m_TextFormat;
	}

	m_PolyMorphRenderTarget->DrawText(
		text.c_str(),
		static_cast<UINT32>(text.length()),
		font,
		D2D1::RectF(static_cast<float>(x), static_cast<float>(y), static_cast<float>(x + TEXTBOX_SIZE.x), static_cast<float>(y + TEXTBOX_SIZE.y)),
		m_Brush[(UINT)color]
	);
}

/// ===================
///		 TRANSFORM
/// ===================

void GraphicsEngine::SetTransform(const D2D1_MATRIX_3X2_F& transformMatrix)
{
	m_PolyMorphRenderTarget->SetTransform(transformMatrix);
}

/// ===================
///		   IMAGE
/// ===================

HRESULT GraphicsEngine::LoadBitmapFromFile(ID2D1Bitmap** image, LPCWSTR imagePath)
{
	// Create Decoder
	IWICBitmapDecoder* decoder = NULL;
	HRESULT hr =
		m_ImagingFactory->CreateDecoderFromFilename(
			imagePath,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&decoder
		);

	// Create the initial frame
	IWICBitmapFrameDecode* frame = NULL;
	if (SUCCEEDED(hr)) hr = decoder->GetFrame(0, &frame);

	// Convert the image format to 32bppPBGRA
	IWICFormatConverter* converter = NULL;
	if (SUCCEEDED(hr)) hr = m_ImagingFactory->CreateFormatConverter(&converter);
	if (SUCCEEDED(hr))
	{
		hr = converter->Initialize(
			frame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	// Create a Direct2D bitmap from the WIC bitmap
	if (SUCCEEDED(hr))
	{
		hr = m_PolyMorphRenderTarget->CreateBitmapFromWicBitmap(
			converter,
			NULL,
			image
		);
	}

	SafeRelease(&decoder);
	SafeRelease(&frame);
	SafeRelease(&converter);

	return hr;
}

/// <summary>
/// 이미지 출력 함수
/// </summary>
/// <param name="image">출력할 이미지</param>
/// <param name="position">이미지 위치(가운데가 원점)</param>
/// <param name="imageSize">이미지 사이즈</param>
/// <param name="sliceStartPosition">시트에서 잘라내기 시작할 위치</param>
/// <param name="sliceSize">시트에서 얼만큼 잘라낼건지</param>
/// <param name="additionalOffset">출력 위치 추가 조정값</param>
void GraphicsEngine::ShowImage(
	ID2D1Bitmap* image,
	Vector2 position,
	Vector2 imageSize,
	Vector2 sliceStartPosition,
	Vector2 sliceSize,
	D2D1_RECT_F additionalOffset,
	float opacity
)
{
	// 이미지를 시트에서 잘라내지 않을 경우(=매개변수로 넣지 않았을 경우)
	// 디폴트값을 만들어준다
	if (sliceStartPosition.x == 999.f &&
		sliceStartPosition.y && 999.f &&
		sliceSize.x == 999.f &&
		sliceSize.y == 999.f)
	{
		sliceSize.x = image->GetSize().width;
		sliceSize.y = image->GetSize().height;
		sliceStartPosition.x = 0;
		sliceStartPosition.y = 0;
	}

	// 시트에서 이미지 잘라내기
	D2D1_RECT_F sliceInfo = {};
	sliceInfo.left = sliceStartPosition.x;
	sliceInfo.right = sliceStartPosition.x + sliceSize.x;
	sliceInfo.top = sliceStartPosition.y;
	sliceInfo.bottom = sliceStartPosition.y + sliceSize.y;

	// 이미지 출력 위치
	D2D1_RECT_F positionInfo = {};
	positionInfo.left = position.x - imageSize.x / 2 + additionalOffset.left;
	positionInfo.right = position.x + imageSize.x / 2 + additionalOffset.right;
	positionInfo.top = position.y - imageSize.y / 2 + additionalOffset.top;
	positionInfo.bottom = position.y + imageSize.y / 2 + additionalOffset.bottom;

	m_PolyMorphRenderTarget->DrawBitmap(
		image,
		positionInfo,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		sliceInfo
	);
}

/// ===================
///		  EFFECT
/// ===================

void GraphicsEngine::TemperatureTintEffect(ID2D1Image* input)
{
	/// Input
	m_TemperatureTintEffect->SetInput(0, input);

	/// Set Value
	// D2D1_TEMPERATUREANDTINT_PROP_TEMPERATURE 속성은 입력 이미지의 온도를 높이거나 줄이는 정도를 지정하는 부동 소수 자릿수 값입니다.
	// 허용되는 범위는 -1.0 ~ 1.0입니다. 기본값은 0.0입니다.
	m_TemperatureTintEffect->SetValue(D2D1_TEMPERATUREANDTINT_PROP_TEMPERATURE, m_TemperatureValue);

	// D2D1_TEMPERATUREANDTINT_PROP_TINT 속성은 입력 이미지의 색조를 늘리거나 줄이는 정도를 지정하는 부동 소수 자릿수 값입니다.
	// 허용되는 범위는 -1.0 ~ 1.0입니다. 기본값은 0.0입니다.
	m_TemperatureTintEffect->SetValue(D2D1_TEMPERATUREANDTINT_PROP_TINT, m_ColorTintValue);
}

void GraphicsEngine::BrightnessEffect(ID2D1Image* input)
{
	// Input
	m_BrightnessEffect->SetInput(0, input);

	/// Set Value
	m_BrightnessEffect->SetValue(D2D1_BRIGHTNESS_PROP_WHITE_POINT, m_WhiteCurvePoint);
	m_BrightnessEffect->SetValue(D2D1_BRIGHTNESS_PROP_BLACK_POINT, m_BlackCurvePoint);
}

ID2D1Bitmap* GraphicsEngine::ConvertImageToBitmap(ID2D1Image* image, D2D1_SIZE_U size)
{
	ID2D1Image* oldTarget = nullptr;
	ID2D1Bitmap1* targetBitmap = nullptr;

	// "D2D1_BITMAP_OPTIONS_TARGET" 모드로 적절한 비트맵을 생성.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
	m_DeviceContext->CreateBitmap(size, 0, 0, bitmapProperties, &targetBitmap);

	// 현재 타겟을 저장 해둔다. 그리고 새로 그릴 ID2D1Bitmap 으로 바꿈.
	m_DeviceContext->GetTarget(&oldTarget);
	m_DeviceContext->SetTarget(targetBitmap);

	// Set Transform
	m_DeviceContext->SetTransform(Matrix3x2F::Identity());
	
	// DC 에 Image를 그림.
	m_DeviceContext->BeginDraw();
	m_DeviceContext->Clear();
	m_DeviceContext->DrawImage(image);
	m_DeviceContext->EndDraw();

	// 비트맵에 해당되는 이미지가 그려졌으므로 해당 비트맵을 리턴한다.
	m_DeviceContext->SetTarget(oldTarget);
	oldTarget->Release();

	return targetBitmap;
}

ID2D1Bitmap* GraphicsEngine::CreateEmptyBitmap(D2D1_SIZE_U size)
{
	ID2D1Bitmap1* targetBitmap = nullptr;
	// "D2D1_BITMAP_OPTIONS_TARGET" 모드로 적절한 비트맵을 생성.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
	m_DeviceContext->CreateBitmap(size, 0, 0, bitmapProperties, &targetBitmap);
	return targetBitmap;
}




