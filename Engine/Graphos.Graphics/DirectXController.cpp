#include "stdafx.h"
#include "DirectXController.h"
#include "WindowController.h"
#include "Config.h"

#include "CgShader.h"

using namespace Graphos::Core;
using namespace Graphos::Graphics;
using namespace DirectX;

void DirectXController::Initialize( void )
{
	WindowController::Get().Initialize();
	WindowController::Get().OpenWindow();

	driverType = D3D_DRIVER_TYPE_HARDWARE;
	enable4xMsaa = false;
	msaa4xQuality = 0;
	device.dxDevice = nullptr;
	deviceContext.dxDeviceContext = nullptr;
	swapChain = nullptr;
	depthStencilBuffer = nullptr;
	renderTargetView = nullptr;
	depthStencilView = nullptr;
	ZeroMemory( &viewport, sizeof(D3D11_VIEWPORT) );

	UINT createDeviceFlags = 0;
#if defined(_DEBUG) || defined(DEBUG)
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL requiredFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL featureLevel;
	
	HRESULT hResult = D3D11CreateDevice(
		NULL,					// Adapter
		driverType,				// Driver Type
		NULL,					// Software
		createDeviceFlags,		// Flags
		&requiredFeatureLevel,	// Feature levels
		1,						// num Feature levels
		D3D11_SDK_VERSION,		// SDK Version
		&device.dxDevice,		// Device
		&featureLevel,			// Feature Level
		&deviceContext.dxDeviceContext );		// Device Context


	// Handle any device creation or DirectX version errors
	if( FAILED(hResult) )
	{
		MessageBox(NULL, L"D3D11CreateDevice Failed", NULL, NULL);
		//return false;
	}

	if( featureLevel != requiredFeatureLevel )
	{
		MessageBox(NULL, L"Direct3D Feature Level 11 unsupported", NULL, NULL);
		//return false;
	}

	// Check for 4X MSAA quality support
	HR(device.dxDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		4,
		&msaa4xQuality));
	//assert( msaa4xQuality > 0 ); // Potential problem if quality is 0
	
	// set up swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc) );
	swapChainDesc.BufferCount							= 1;
	swapChainDesc.BufferDesc.Width						= WindowController::Get().GetWidth();//windowWidth;
	swapChainDesc.BufferDesc.Height						= WindowController::Get().GetHeight();//windowHeight;
	swapChainDesc.BufferDesc.RefreshRate.Numerator		= 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator	= 1;
	swapChainDesc.BufferDesc.Format						= DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow							= WindowController::Get().GetHWnd();//hMainWnd;
	swapChainDesc.Windowed								= true;
	swapChainDesc.Flags									= 0;

	if( enable4xMsaa )
	{ // Set up 4x MSAA
		swapChainDesc.SampleDesc.Count   = 4;
		swapChainDesc.SampleDesc.Quality = msaa4xQuality - 1;
	}
	else
	{ // No MSAA
		swapChainDesc.SampleDesc.Count   = 1;
		swapChainDesc.SampleDesc.Quality = 0;
	}

	// To correctly create the swap chain, we must use the IDXGIFactory that
	// was used to create the device.
	IDXGIDevice*	dxgiDevice	= 0;
	IDXGIAdapter*	dxgiAdapter = 0;
	IDXGIFactory*	dxgiFactory = 0;
	HR(device.dxDevice->QueryInterface(	__uuidof(IDXGIDevice),	(void**)&dxgiDevice));
	HR(dxgiDevice->GetParent(	__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));
	HR(dxgiAdapter->GetParent(	__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	// Finally make the swap chain and release the DXGI stuff
	HR(dxgiFactory->CreateSwapChain(device.dxDevice, &swapChainDesc, &swapChain));
	ReleaseCOMobjMacro(dxgiDevice);
	ReleaseCOMobjMacro(dxgiAdapter);
	ReleaseCOMobjMacro(dxgiFactory);

	// The remaining steps also need to happen each time the window
	// is resized, so just run the OnResize method
	Resize();

	CgShader::InitCg();
}

void DirectXController::Shutdown( void )
{
	CgShader::ShutdownCg();

	// Release the DX stuff
	ReleaseCOMobjMacro( renderTargetView );
	ReleaseCOMobjMacro( depthStencilView );
	ReleaseCOMobjMacro( swapChain );
	ReleaseCOMobjMacro( depthStencilBuffer );

	// Restore default device settings
	if( deviceContext.dxDeviceContext )
		deviceContext.dxDeviceContext->ClearState();

	// Release the context and finally the device
	ReleaseCOMobjMacro(deviceContext.dxDeviceContext);
	
#if defined(_DEBUG) || defined(DEBUG)
	ID3D11Debug* debugDev;
	device.dxDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));
	debugDev->ReportLiveDeviceObjects( D3D11_RLDO_DETAIL );
#endif
	ReleaseCOMobjMacro(device.dxDevice);

}

void DirectXController::Resize( void )
{
	// release old views
	ReleaseCOMobjMacro(renderTargetView);
	ReleaseCOMobjMacro(depthStencilView);
	ReleaseCOMobjMacro(depthStencilBuffer);

	// resize swap chain
	HR( swapChain->ResizeBuffers(
			1,			// BufferCount
			WindowController::Get().GetWidth(),
			WindowController::Get().GetHeight(),
			DXGI_FORMAT_R8G8B8A8_UNORM,	
			0)		// Swap chain flags
	);
	
	// create render target view
	ID3D11Texture2D* backBuffer;
	HR( swapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer ) );
	HR( device.dxDevice->CreateRenderTargetView( backBuffer, NULL, &renderTargetView ) );
	ReleaseCOMobjMacro( backBuffer );

	// Set up the description of the texture to use for the
	// depth stencil buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width			= WindowController::Get().GetWidth();//windowWidth;
	depthStencilDesc.Height			= WindowController::Get().GetHeight();//windowHeight;
	depthStencilDesc.MipLevels		= 1;
	depthStencilDesc.ArraySize		= 1;
	depthStencilDesc.Format			= DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags      = 0;
	if( enable4xMsaa )
	{ // Turn on 4x MultiSample Anti Aliasing
		// This must match swap chain MSAA values
		depthStencilDesc.SampleDesc.Count	= 4;
		depthStencilDesc.SampleDesc.Quality = msaa4xQuality - 1;
	}
	else
	{ // No MSAA
		depthStencilDesc.SampleDesc.Count   = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	// Create the depth/stencil buffer and corresponding view
	HR(device.dxDevice->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer));
	HR(device.dxDevice->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView));

	// Bind these views to the pipeline, so rendering actually uses the underlying textures
	deviceContext.dxDeviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	// Update the viewport and set it on the device
	viewport.TopLeftX	= 0;
	viewport.TopLeftY	= 0;
	viewport.Width		= (float)WindowController::Get().GetWidth();
	viewport.Height		= (float)WindowController::Get().GetHeight();
	viewport.MinDepth	= 0.0f;
	viewport.MaxDepth	= 1.0f;

	deviceContext.dxDeviceContext->RSSetViewports(1, &viewport);
}

void DirectXController::Reload( void )
{
	Resize();
}


void DirectXController::BeginDraw( void )
{
	float ClearColor[4] = { 100.0f/255.0f, 149.0f/255.0f, 237.0f/255.0f, 1.0f };
	// Clear the back buffer        
	deviceContext.dxDeviceContext->ClearRenderTargetView( renderTargetView, ClearColor );
	deviceContext.dxDeviceContext->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0 );
}

void DirectXController::EndDraw( void )
{
	swapChain->Present( 0, 0 );
}
