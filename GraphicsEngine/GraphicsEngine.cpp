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

	// WIC Imaging Factory ����
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

	// Write Factory ����
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

	// Device Dependent Resources ����
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
		// Device Context ����
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
	// API �⺻���� �ٸ� ���� ä�� ������ �����ϱ� ���� �÷����Դϴ�.
	// Direct2D���� ȣȯ���� ���� �ʿ��մϴ�.
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	// �� �迭�� �� ���� �����ϴ� DirectX �ϵ���� ��� ������ �����մϴ�.
	// ������ �߿��ϸ� �� �����ؾ� �մϴ�.
	// ���� �ּ� �䱸 ��� ������ ���� �����ϴ� ���� ���� ������.
	// ��� ���� �׷��� ���� �� 9.1�� �����ϴ� ������ �����˴ϴ�.
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

	// DX11 API ��ġ ��ü�� ����� �ش� ���ؽ�Ʈ�� �����ɴϴ�.
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	DX::ThrowIfFailed(
		D3D11CreateDevice(
			nullptr,                    // �⺻ ����� ����� ���� null ����
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			creationFlags,              // ����� �� Direct2D ȣȯ�� �÷��� ���������� ����
			featureLevels,              // �� ���� ������ �� �ִ� ��� ���� ���
			ARRAYSIZE(featureLevels),   // ������ ��� ������ ��
			D3D11_SDK_VERSION,
			&device,                    // ������ Direct3D ��ġ ��ȯ
			&m_FeatureLevel,		    // ������ ��ġ�� ��� ���� ��ȯ
			&context                    // ��ġ�� ��� ���ؽ�Ʈ ��ȯ
		)
	);

	
	ComPtr<IDXGIDevice1> dxgiDevice;

	// Direct3D11 ��ġ�� �⺻ DXGI ��ġ�� �����ɴϴ�.
	DX::ThrowIfFailed(
		device.As(&dxgiDevice)
	);

	// 2D �������� ���� Direct2D ��ġ�� �����ɴϴ�.
	DX::ThrowIfFailed(
		m_D2DFactory->CreateDevice(dxgiDevice.Get(), &m_D2DDevice)
	);

	// Direct2D ��ġ�� �ش��ϴ� ��ġ ���ؽ�Ʈ ��ü�� �����ɴϴ�.
	DX::ThrowIfFailed(
		m_D2DDevice->CreateDeviceContext(
			D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&m_DeviceContext
		)
	);

	

	// ��ũ���� �Ҵ�.
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Width = 0;										// �ڵ� ũ�� ���� ���
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// ���� �Ϲ����� ���� ü�� ����
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;								// ��Ƽ���ø� ������� ����
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;									// ���� ���۸� ����Ͽ� �ø� �����ϰ� ��
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	// ��� ���� �� SwapEffect�� ����ؾ� ��
	swapChainDesc.Flags = 0;

	// �� ��ġ�� ����Ǵ� ������ �����(GPU �Ǵ� ī��)�� �ĺ�.
	ComPtr<IDXGIAdapter> dxgiAdapter;
	DX::ThrowIfFailed(
		dxgiDevice->GetAdapter(&dxgiAdapter)
	);

	// �� DXGI ��ġ�� ���� ���丮 ��ü ��������.
	ComPtr<IDXGIFactory2> dxgiFactory;
	DX::ThrowIfFailed(
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
	);

	// DXGI ���丮���� �� �����쿡 ���� ���� ���� ü�� ��������.
// 	DX::ThrowIfFailed(
// 		dxgiFactory->CreateSwapChainForCoreWindow(
// 			device.Get(),
// 			reinterpret_cast<IUnknown*>(m_Hwnd),
// 			&swapChainDesc,
// 			nullptr,    // ��� ���÷��̿��� ���
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
		&swapChainDescFull, // ��üȭ�� ����ü�� ����
		nullptr,
		&m_SwapChain);

	// DXGI�� ���ÿ� �ϳ� �̻��� �������� ������� �ʵ��� ����.
	DX::ThrowIfFailed(
		dxgiDevice->SetMaximumFrameLatency(1)
	);

	// �� �����쿡 ���� ����۸� �����ͼ� ���� 3D ������ ������� ���.
	ComPtr<ID3D11Texture2D> backBuffer;
	DX::ThrowIfFailed(
		m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))
	);

	// DPI�� �����´�
	float dpi;
	dpi = (float)GetDpiForWindow(m_Hwnd);

	// ���� ���� ü�ΰ� ����� Direct2D ���� Ÿ�� ��Ʈ���� ����.
	// �� ��Ʈ�ʿ� �������� ������ ������� ����� ���� ü�ο� ���� �������˴ϴ�.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			dpi,
			dpi
		);

	// Direct2D�� ����� ���ǽ� �������� DXGI ������ �ʿ�� �մϴ�.
	ComPtr<IDXGISurface> dxgiBackBuffer;
	DX::ThrowIfFailed(
		m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer))
	);

	// DXGI ����ۿ��� D2D ���� Ÿ������ ����� D2D ���ǽ� ��������.
	DX::ThrowIfFailed(
		m_DeviceContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer.Get(),
			&bitmapProperties,
			&m_OriginalBuffer
		)
	);

	// ���� Direct2D ���� Ÿ���� ����.
	m_DeviceContext->SetTarget(m_OriginalBuffer);

	/// ���⼭���� �߰���Ʈ�� �����
	/// ���� ������ ��� �� ȣȯ�Ǵ� �߰� ������ũ�� �׸��� �߿� ����� �� ��Ʈ�� ������ ����� ����ϴ�.
	if (!m_DeviceContext) return S_FALSE;
	HRESULT hr = m_DeviceContext->CreateCompatibleRenderTarget(
		m_DeviceContext->GetSize(),
		&m_CompatibleRenderTarget
	);

	m_PolyMorphRenderTarget = m_DeviceContext;


	/// �������

	return S_OK;
}

void GraphicsEngine::DiscardDeviceResources()
{
	// COM �������̽� ����
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
		parameters.DirtyRectsCount = 0;			// 0�̸� ��ü ������ ������Ʈ
		parameters.pDirtyRects = nullptr;		// DirtyRectsCount�� 0�̸� NULL�� ���� ����
		parameters.pScrollRect = nullptr;		// NULL�̸� �������� ���� �����ӿ��� ��ũ�ѵ��� ����
		parameters.pScrollOffset = nullptr;		// NULL�̸� ������ ����

		DX::ThrowIfFailed(
			m_SwapChain->Present1(1, 0, &parameters)
		);

		// �ڿ��� �����ؾ� �� ���
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
	LPCSTR path = "����";
	int font = AddFontResourceA(path);
	SendMessageA(HWND_BROADCAST, WM_FONTCHANGE, NULL, NULL);

	LPCWSTR fontName = L"����";
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
/// �̹��� ��� �Լ�
/// </summary>
/// <param name="image">����� �̹���</param>
/// <param name="position">�̹��� ��ġ(����� ����)</param>
/// <param name="imageSize">�̹��� ������</param>
/// <param name="sliceStartPosition">��Ʈ���� �߶󳻱� ������ ��ġ</param>
/// <param name="sliceSize">��Ʈ���� ��ŭ �߶󳾰���</param>
/// <param name="additionalOffset">��� ��ġ �߰� ������</param>
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
	// �̹����� ��Ʈ���� �߶��� ���� ���(=�Ű������� ���� �ʾ��� ���)
	// ����Ʈ���� ������ش�
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

	// ��Ʈ���� �̹��� �߶󳻱�
	D2D1_RECT_F sliceInfo = {};
	sliceInfo.left = sliceStartPosition.x;
	sliceInfo.right = sliceStartPosition.x + sliceSize.x;
	sliceInfo.top = sliceStartPosition.y;
	sliceInfo.bottom = sliceStartPosition.y + sliceSize.y;

	// �̹��� ��� ��ġ
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
	// D2D1_TEMPERATUREANDTINT_PROP_TEMPERATURE �Ӽ��� �Է� �̹����� �µ��� ���̰ų� ���̴� ������ �����ϴ� �ε� �Ҽ� �ڸ��� ���Դϴ�.
	// ���Ǵ� ������ -1.0 ~ 1.0�Դϴ�. �⺻���� 0.0�Դϴ�.
	m_TemperatureTintEffect->SetValue(D2D1_TEMPERATUREANDTINT_PROP_TEMPERATURE, m_TemperatureValue);

	// D2D1_TEMPERATUREANDTINT_PROP_TINT �Ӽ��� �Է� �̹����� ������ �ø��ų� ���̴� ������ �����ϴ� �ε� �Ҽ� �ڸ��� ���Դϴ�.
	// ���Ǵ� ������ -1.0 ~ 1.0�Դϴ�. �⺻���� 0.0�Դϴ�.
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

	// "D2D1_BITMAP_OPTIONS_TARGET" ���� ������ ��Ʈ���� ����.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
	m_DeviceContext->CreateBitmap(size, 0, 0, bitmapProperties, &targetBitmap);

	// ���� Ÿ���� ���� �صд�. �׸��� ���� �׸� ID2D1Bitmap ���� �ٲ�.
	m_DeviceContext->GetTarget(&oldTarget);
	m_DeviceContext->SetTarget(targetBitmap);

	// Set Transform
	m_DeviceContext->SetTransform(Matrix3x2F::Identity());
	
	// DC �� Image�� �׸�.
	m_DeviceContext->BeginDraw();
	m_DeviceContext->Clear();
	m_DeviceContext->DrawImage(image);
	m_DeviceContext->EndDraw();

	// ��Ʈ�ʿ� �ش�Ǵ� �̹����� �׷������Ƿ� �ش� ��Ʈ���� �����Ѵ�.
	m_DeviceContext->SetTarget(oldTarget);
	oldTarget->Release();

	return targetBitmap;
}

ID2D1Bitmap* GraphicsEngine::CreateEmptyBitmap(D2D1_SIZE_U size)
{
	ID2D1Bitmap1* targetBitmap = nullptr;
	// "D2D1_BITMAP_OPTIONS_TARGET" ���� ������ ��Ʈ���� ����.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
	m_DeviceContext->CreateBitmap(size, 0, 0, bitmapProperties, &targetBitmap);
	return targetBitmap;
}




