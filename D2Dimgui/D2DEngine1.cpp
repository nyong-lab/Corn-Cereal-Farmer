// D2DEngine.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "D2DEngine1.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")			// writefactory
#pragma comment(lib, "windowscodecs.lib")	// WIC

/// 밑에서부터 dc
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")			// DXGI

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

/// 이미지 불러올때 쓸 헤더
#define STB_IMAGE_IMPLEMENTATION
#include "../D2Dimgui//stb_image.h"

D2DEngine1* D2DEngine1::engineInstance = nullptr;

// TODO: 라이브러리 함수의 예제입니다.

D2DEngine1::D2DEngine1() :
	m_Hwnd(NULL),
	m_D2DFactory(nullptr),
	m_RenderTarget(nullptr),
	m_WICFactory(nullptr),
	m_BlackBrush(nullptr),
	m_SelectedBrush(nullptr),
	m_TempBrush(nullptr),
	m_DWriteFactory(nullptr),
	m_TextFormat(nullptr),
	m_PathGeometry(nullptr),
	m_FeatureLevel(),
	m_D2DDevice(nullptr),
	m_DeviceContext(nullptr),
	m_D2DTargetBitmap(nullptr),
	m_SwapChain(nullptr),
	m_ResizeHeight(0),
	m_ResizeWidth(0),
	m_dpi(0.f),
	m_MainRenderTargetView(nullptr),
	m_D3DDevice(nullptr),
	m_D3DDeviceContext(nullptr)


{

}

D2DEngine1::~D2DEngine1()
{
	SafeRelease(&m_D2DFactory);
	SafeRelease(&m_RenderTarget);
	SafeRelease(&m_WICFactory);
	SafeRelease(&m_BlackBrush);
	SafeRelease(&m_SelectedBrush);
	SafeRelease(&m_TempBrush);
	SafeRelease(&m_DWriteFactory);
	SafeRelease(&m_TextFormat);
	SafeRelease(&m_PathGeometry);
	SafeRelease(&m_D2DDevice);
	SafeRelease(&m_DeviceContext);
	SafeRelease(&m_D2DTargetBitmap);
	SafeRelease(&m_SwapChain);
	SafeRelease(&m_MainRenderTargetView);
	SafeRelease(&m_D3DDevice);
	SafeRelease(&m_D3DDeviceContext);
	CoUninitialize();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

HRESULT D2DEngine1::Initialize(HWND hwnd)
{
	HRESULT hr = S_OK;
	m_Hwnd = hwnd;
	hr = CoInitialize(NULL);
	CreateDeviceIndependentResources();
	

	if (SUCCEEDED(hr))
	{
		// WIC Factory 인터페이스 얻기
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&g_pIWICImagingFactory)
		);
	}




	return hr;
}

HRESULT D2DEngine1::CreateDeviceIndependentResources()
{

	static const WCHAR fontName[] = L"Verdana";
	static const FLOAT fontSize = 12;		// 초기 폰트 사이즈는 이렇게 만들어본다..


	HRESULT hr = S_OK;
	ID2D1GeometrySink* pSink = NULL;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_D2DFactory);
	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance( //COM(Component Object Model) 객체를 생성하기 위해 사용되는 함수
			CLSID_WICImagingFactory, // WIC Imaging Factory에 대한 클래스 식별자
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory, // WIC Imaging Factory 인터페이스의 GUID 식별자
			reinterpret_cast<void**>(&m_WICFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// 다이렉트 라이트 팩토리 생성
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_DWriteFactory),
			reinterpret_cast<IUnknown**>(&m_DWriteFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// 텍스트 포멧 생성
		hr = m_DWriteFactory->CreateTextFormat(
			fontName,
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,
			L"",
			&m_TextFormat
		);
	}

	if (SUCCEEDED(hr))
	{
		m_TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING); // 일단 수평에서는 왼쪽정렬 해본다.. 그게편할듯..
		m_TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR); // 일단 수직방향에서는 위쪽정렬로 한다... 그게 편할듯..
	}


	return hr;
}

HRESULT D2DEngine1::CreateDeviceResources()
{
	HRESULT hr = S_OK;


	if (!m_DeviceContext)
	{
		/// 이거 여기 두는게 맞는거같다..
		/// 맨날맨날 만들줄 알았지만 사실 한번밖에 실행 안하는코드!
		CreateDeviceContext();

		CreateRenderTarget();


		///imgui 세팅
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls 
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(m_Hwnd);
		ImGui_ImplDX11_Init(m_D3DDevice, m_D3DDeviceContext);

		RECT rc;
		GetClientRect(m_Hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			static_cast<UINT>(rc.right - rc.left),
			static_cast<UINT>(rc.bottom - rc.top)
		);

		// Create a Direct2D render target.
		/// 이건 렌더타겟 전용인듯하다.
		/// dc로 바꾸지않게 주의하자
// 		hr = m_D2DFactory->CreateHwndRenderTarget(
// 			D2D1::RenderTargetProperties(), // 기본 렌더링 대상 속성
// 			D2D1::HwndRenderTargetProperties(m_Hwnd, size),  // 생성할 렌더링 대상의 윈도우 핸들과 크기를 나타내는 구조체
// 			&m_RenderTarget
// 		);

		hr = m_DeviceContext->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&m_BlackBrush
		);

		// 일단 선택한 브러쉬 색깔 초기값은 라임색으로 지정
		hr = m_DeviceContext->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Lime),
			&m_SelectedBrush
		);
	}


	return hr;
}

/// <summary>
/// 이건 한번만 하면 되는가? 실험해보자
/// </summary>
/// <returns></returns>
HRESULT D2DEngine1::CreateDeviceContext()
{
	// This flag adds support for surfaces with a different color channel ordering than the API default.
  // You need it for compatibility with Direct2D.
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	// This array defines the set of DirectX hardware feature levels this app  supports.
	// The ordering is important and you should  preserve it.
	// Don't forget to declare your app's minimum required feature level in its
	// description.  All apps are assumed to support 9.1 unless otherwise stated.
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

	// Create the DX11 API device object, and get a corresponding context.
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;

	DX::ThrowIfFailed(
		D3D11CreateDevice(
			nullptr,                    // specify null to use the default adapter
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			creationFlags,              // optionally set debug and Direct2D compatibility flags
			featureLevels,              // list of feature levels this app can support
			ARRAYSIZE(featureLevels),   // number of possible feature levels
			D3D11_SDK_VERSION,
			&device,                    // returns the Direct3D device created
			&m_FeatureLevel,            // returns feature level of device created
			&context                    // returns the device immediate context
		)
	);

	m_D3DDevice = device.Get();
	m_D3DDeviceContext = context.Get();
	/// 여기서 1써줬는데 맞는지 모르겠댜..
	ComPtr<IDXGIDevice1> dxgiDevice;
	// Obtain the underlying DXGI device of the Direct3D11 device.
	DX::ThrowIfFailed(
		device.As(&dxgiDevice)
	);

	// Obtain the Direct2D device for 2-D rendering.
	DX::ThrowIfFailed(
		m_D2DFactory->CreateDevice(dxgiDevice.Get(), &m_D2DDevice)
	);

	// Get Direct2D device's corresponding device context object.
	DX::ThrowIfFailed(
		m_D2DDevice->CreateDeviceContext(
			D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&m_DeviceContext
		)
	);


	// Allocate a descriptor.
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Width = 0;                           // use automatic sizing
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // this is the most common swapchain format
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;                // don't use multi-sampling
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;                     // use double buffering to enable flip
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // all apps must use this SwapEffect
	swapChainDesc.Flags = 0;

	// Identify the physical adapter (GPU or card) this device is runs on.
	ComPtr<IDXGIAdapter> dxgiAdapter;
	DX::ThrowIfFailed(
		dxgiDevice->GetAdapter(&dxgiAdapter)
	);

	// Get the factory object that created the DXGI device.
	ComPtr<IDXGIFactory2> dxgiFactory;
	DX::ThrowIfFailed(
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
	);

	/// 교수님코드는 여기서 전체화면~~~ 해줬다.
	///
	/// 밑에꺼 도저히 이해할수가 없다...

	// Get the final swap chain for this window from the DXGI factory.
// 	DX::ThrowIfFailed(
// 		dxgiFactory->CreateSwapChainForCoreWindow(
// 			device.Get(),
// 			reinterpret_cast<IUnknown*>(window), /// 이거맞나 확인해보자
// 			&swapChainDesc,
// 			nullptr,    // allow on all displays
// 			&m_SwapChain
// 		)
// 	);

	/// 교슈님 코드
	DXGI_RATIONAL rate;
	rate.Denominator = 60;
	rate.Numerator = 1;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainDescFull;
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

	///여기서 이거 하려면 device1해줘야한다.
	// Ensure that DXGI doesn't queue more than one frame at a time.
	DX::ThrowIfFailed(
		dxgiDevice->SetMaximumFrameLatency(1)
	);

	// Get the backbuffer for this window which is be the final 3D render target.
	ComPtr<ID3D11Texture2D> backBuffer;
	DX::ThrowIfFailed(
		m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))
	);

	/// D2D1 네임스페이스 써줬다.
	// Now we set up the Direct2D render target bitmap linked to the swapchain. 
	// Whenever we render to this bitmap, it is directly rendered to the 
	// swap chain associated with the window.
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			m_dpi,
			m_dpi
		);

	// Direct2D needs the dxgi version of the backbuffer surface pointer.
	ComPtr<IDXGISurface> dxgiBackBuffer;
	DX::ThrowIfFailed(
		m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer))
	);

	// Get a D2D surface from the DXGI back buffer to use as the D2D render target.
	DX::ThrowIfFailed(
		m_DeviceContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer.Get(),
			&bitmapProperties,
			&m_D2DTargetBitmap
		)
	);

	// Now we can set the Direct2D render target.
	m_DeviceContext->SetTarget(m_D2DTargetBitmap);

	return S_OK;
}


void D2DEngine1::BeginRender()
{
	HRESULT hr;

	hr = CreateDeviceResources();


	// Handle window resize (we don't resize directly in the WM_SIZE handler)
	if (m_ResizeWidth != 0 && m_ResizeHeight != 0)
	{
		CleanupRenderTarget();
		m_SwapChain->ResizeBuffers(0, m_ResizeWidth, m_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
		m_ResizeWidth = m_ResizeHeight = 0;
		CreateRenderTarget();
	}

	// Start the Dear ImGui frame





	// 비긴페인트냐?
 	m_DeviceContext->BeginDraw();

	//m_DeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());

	

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void D2DEngine1::EndRender()
{

	/// IDXGISwapChain::Present 메서드를 호출하여 결과를 표시합니다 .
	/// 더블버퍼링 느낌인거같다?
	/// [in] pPresentParameters
	///표시할 프레임의 업데이트된 사각형 및 스크롤 정보를 설명하는 
	///DXGI_PRESENT_PARAMETERS 구조 에 대한 포인터입니다 .
	/// typedef struct DXGI_PRESENT_PARAMETERS {
	///   UINT  DirtyRectsCount;
	///   RECT  *pDirtyRects;
	///   RECT  *pScrollRect;
	///   POINT *pScrollOffset;
	/// } DXGI_PRESENT_PARAMETERS;
	/// 




	m_DeviceContext->EndDraw();
	
	//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// imgui Rendering
	ImGui::Render();
	//const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
	m_D3DDeviceContext->OMSetRenderTargets(1, &m_MainRenderTargetView, nullptr);
	//m_pd3dDeviceContext->ClearRenderTargetView(m_mainRenderTargetView, clear_color_with_alpha);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// 엔드페인트냐?


	DXGI_PRESENT_PARAMETERS parameters;
	parameters.DirtyRectsCount = 0;
	parameters.pDirtyRects = nullptr;
	parameters.pScrollRect = nullptr;
	parameters.pScrollOffset = nullptr;



	DX::ThrowIfFailed(
		m_SwapChain->Present1(1, 0, &parameters)
	);

}

void D2DEngine1::SelectBrush(D2D1::ColorF colorF)
{
	SafeRelease(&m_SelectedBrush);


	m_DeviceContext->CreateSolidColorBrush(
		colorF,
		&m_SelectedBrush
	);
}

void D2DEngine1::FillRectangle(int left, int top, int right, int bottom)
{
	if (m_SelectedBrush != NULL)
	{
		D2D1_RECT_F rect;
		rect.left = (float)left;
		rect.top = (float)top;
		rect.right = (float)right;
		rect.bottom = (float)bottom;

		m_DeviceContext->FillRectangle(rect, m_SelectedBrush);
	}
}

void D2DEngine1::FillRectangle(int left, int top, int right, int bottom, D2D1::ColorF colorF)
{
	m_DeviceContext->CreateSolidColorBrush(
		colorF,
		&m_TempBrush
	);

	if (m_TempBrush != NULL)
	{
		D2D1_RECT_F rect;
		rect.left = (float)left;
		rect.top = (float)top;
		rect.right = (float)right;
		rect.bottom = (float)bottom;

		m_DeviceContext->FillRectangle(rect, m_TempBrush);
	}

	SafeRelease(&m_TempBrush);
}

void D2DEngine1::DrawRectangle(int left, int top, int right, int bottom)
{
	if (m_SelectedBrush != NULL)
	{
		D2D1_RECT_F rect;
		rect.left = (float)left;
		rect.top = (float)top;
		rect.right = (float)right;
		rect.bottom = (float)bottom;

		m_DeviceContext->DrawRectangle(rect, m_SelectedBrush, 1.f);
	}
}


void D2DEngine1::DrawRectangle(int left, int top, int right, int bottom, D2D1::ColorF colorF)
{
	m_DeviceContext->CreateSolidColorBrush(
		colorF,
		&m_TempBrush
	);

	if (m_TempBrush != NULL)
	{
		D2D1_RECT_F rect;
		rect.left = (float)left;
		rect.top = (float)top;
		rect.right = (float)right;
		rect.bottom = (float)bottom;

		m_DeviceContext->DrawRectangle(rect, m_TempBrush, 1.f);
	}

	SafeRelease(&m_TempBrush);
}

void D2DEngine1::DrawOrientedRectangle(int left, int top, int right, int bottom, float rotation)
{
	if (m_SelectedBrush != NULL)
	{
		D2D1_RECT_F rect;
		rect.left = (float)left;
		rect.top = (float)top;
		rect.right = (float)right;
		rect.bottom = (float)bottom;

		m_DeviceContext->SetTransform(
			D2D1::Matrix3x2F::Rotation(
				rotation,
				D2D1::Point2F(
					float(left + right) / 2.f,
					float(top + bottom) / 2.f))
		);
		m_DeviceContext->DrawRectangle(rect, m_SelectedBrush, 1.f);

		m_DeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

void D2DEngine1::DrawLine(int startX, int StartY, int endX, int endY, float stroke) {
	m_DeviceContext->DrawLine(
		D2D1_POINT_2F{ float(startX), float(StartY) },
		D2D1_POINT_2F{ float(endX), float(endY) },
		m_SelectedBrush, stroke);
}

void D2DEngine1::DrawLine(int centerX, int centerY, int scale, float rotation)
{
	// 	m_RenderTarget->SetTransform(
	// 		D2D1::Matrix3x2F::Rotation(
	// 			rotation,
	// 			D2D1::Point2F(
	// 				float(centerX),
	// 				float(centerY)))
	// 	);

	m_DeviceContext->DrawLine(
		D2D1_POINT_2F{ float(centerX), float(centerY) - scale / 2.f },
		D2D1_POINT_2F{ float(centerX), float(centerY) + scale / 2.f },
		m_SelectedBrush, 1.f);

	// 	m_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());


}
void D2DEngine1::DrawCircle(int centerX, int centerY, int radius)
{
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1_POINT_2F{ float(centerX), float(centerY) }, float(radius), float(radius));
	m_DeviceContext->DrawEllipse(ellipse, m_SelectedBrush, 1.0f);
}


void D2DEngine1::PrintText()
{
	/*	msdn코드 수정 필요*/
	D2D1_SIZE_F dcSize = m_DeviceContext->GetSize();
	m_DeviceContext->DrawText(
 			L"sc_helloWorld",
 			wcslen(L"sc_helloWorld") - 1,
			m_TextFormat,
 			D2D1::RectF(0, 0, dcSize.width, dcSize.height),
 			m_BlackBrush
 		);

}

void D2DEngine1::DrawPolygon(D2D1_POINT_2F points[], const int pointsCount)
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

		m_DeviceContext->DrawGeometry(m_PathGeometry, m_SelectedBrush, 1.f);

		SafeRelease(&pSink);
		SafeRelease(&m_PathGeometry);
	}
}

void D2DEngine1::SetTransform(D2D1::Matrix3x2F matrix3x2F)
{
	m_DeviceContext->SetTransform(matrix3x2F);
}

void D2DEngine1::Clear(D2D1::ColorF colorF)
{
	m_DeviceContext->Clear(colorF); // 배경그리기 정도...? 로 해석중 일단..
}


HRESULT D2DEngine1::CreateD2DBitmapFromFile(const std::wstring& imageName, const LPCWSTR& imagePath)
{
	HRESULT hr;
	// 디코더 생성
	IWICBitmapDecoder* pDecoder = NULL;

	hr = g_pIWICImagingFactory->CreateDecoderFromFilename(
		imagePath,                      // Image to be decoded
		NULL,                            // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// 디코더에서 0번째 프레임 정보를 검색
	IWICBitmapFrameDecode* pFrame = NULL;

	//0번째 프레임 정보를 가지고 옴
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	IWICFormatConverter* pConverter = NULL;

	//Step 3: 포멧변화 -> 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		hr = g_pIWICImagingFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			NULL,                            // Specify a particular palette 
			0.0f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}

	//비트맵 생성
	ID2D1Bitmap* bitmap = nullptr;

	if (SUCCEEDED(hr))
	{
		hr = m_DeviceContext->CreateBitmapFromWicBitmap(pConverter, nullptr, &bitmap);
	}

	//map에 저장
	images[imageName] = bitmap;


	if (pFrame != NULL)
		pFrame->Release();

	if (pConverter != NULL)
		pConverter->Release();

	if (pDecoder != NULL)
		pDecoder->Release();

	return hr;
}

ID2D1Bitmap* D2DEngine1::getImage(const std::wstring& imageName)
{
	ID2D1Bitmap* img = findImage(imageName);

	return img;
}

ID2D1Bitmap* D2DEngine1::findImage(const std::wstring& imageName)
{
	std::map<std::wstring, ID2D1Bitmap*> ::iterator iter = images.find(imageName);
	if (iter == images.end())
	{
		return nullptr;
	}

	return (ID2D1Bitmap*)iter->second;
}

bool D2DEngine1::DrawBitMaps(ID2D1Bitmap* bitMap)
{
	m_DeviceContext->DrawBitmap(bitMap);

	return true;
}

void D2DEngine1::CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	if (pBackBuffer != 0)
	{
		m_D3DDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_MainRenderTargetView);
	}
		
	pBackBuffer->Release();
}

void D2DEngine1::CleanupRenderTarget()
{
	if (m_MainRenderTargetView) { m_MainRenderTargetView->Release(); m_MainRenderTargetView = nullptr; }
}

bool D2DEngine1::LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	m_D3DDevice->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	m_D3DDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
	pTexture->Release();

	*out_width = image_width;
	*out_height = image_height;
	stbi_image_free(image_data);

	return true;
}

D2D1::ColorF D2DEngine1::ColorF(float red, float green, float blue, float alpha /*= 1.0f*/)
{
	return D2D1::ColorF(red, green, blue, alpha);
}

