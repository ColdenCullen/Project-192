
#include "DXGame.h"
#include <windowsx.h>

#pragma region Global Window Callback
namespace
{
	// Allows us to forward Windows messages from a global
	// window procedure to our member function window procedure
	// because we cannot assign a member function to WNDCLASS::lpfnWndProc
	DXGame* dxGame = 0;
}

// Set up a global callback for handling windows messages
LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward the global callback to our game's message handling
	// Forward hwnd because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return dxGame->MsgProc(hwnd, msg, wParam, lParam);
}
#pragma endregion

DXGame::DXGame(HINSTANCE hInstance)
:	hAppInst(hInstance),
	windowCaption(L"DirectX Game"),
	driverType(D3D_DRIVER_TYPE_HARDWARE),
	windowWidth(800),
	windowHeight(600),
	enable4xMsaa(false),
	hMainWnd(0),
	gamePaused(false),
	minimized(false),
	maximized(false),
	resizing(false),
	msaa4xQuality(0),

	device(0),
	deviceContext(0),
	swapChain(0),
	depthStencilBuffer(0),
	renderTargetView(0),
	depthStencilView(0)
{
	// Zero out the viewport struct
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	// Grabs a pointer to this DXGame object so we can forward
	// Windows messages to the object's message handling function
	dxGame = this;
}


DXGame::~DXGame(void)
{
	// clean up Cg stuff
	CleanUpCg();


	// Release the DX stuff
	ReleaseCOMobjMacro(renderTargetView);
	ReleaseCOMobjMacro(depthStencilView);
	ReleaseCOMobjMacro(swapChain);
	ReleaseCOMobjMacro(depthStencilBuffer);

	// Restore default device settings
	if( deviceContext )
		deviceContext->ClearState();

	// Release the context and finally the device
	ReleaseCOMobjMacro(deviceContext);
	ReleaseCOMobjMacro(device);
}

int DXGame::run()
{
	MSG msg = {0};
	
	// Loop until we get a quit message from windows
	while(msg.message != WM_QUIT)
	{
		// Peek at the next message (and remove it from the queue)
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			// Handle this message
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			// No message, so continue the game loop
			//timer.Tick();

		//	if( gamePaused )
		//	{
		//		Sleep(100);
		//	}
		//	else
		//	{
				// Standard game loop type stuff
				//CalculateFrameStats();
			//	UpdateScene(timer.DeltaTime());
				DrawScene();
		//	}
		}
	}

	return (int)msg.wParam;
}

bool DXGame::Init()
{
	if( !InitMainWindow() )
		return false;

	if( !InitDirect3D() )
		return false;

	if( !InitCg() )
		return false;

	return true;
}

bool DXGame::InitMainWindow()
{
	WNDCLASSEX wc;
	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= MainWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hAppInst;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW +1 );
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= "DirectX 11 and Cg Demo";
	wc.hIconSm			= NULL;

	if( !RegisterClassEx(&wc) )
	{
		MessageBox(NULL,"RegisterClass Failed.", NULL,NULL);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, windowWidth, windowHeight };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width  = R.right - R.left;
	int height = R.bottom - R.top;

	hMainWnd = CreateWindow( wc.lpszClassName,          // Class name
                           wc.lpszClassName,          // Window name
                           WS_OVERLAPPEDWINDOW,    // Style
                           CW_USEDEFAULT,          // X position
                           CW_USEDEFAULT,          // Y position
                           width,				// Width
                           height,				// Height
                           NULL,                   // Parent HWND
                           NULL,                   // Menu
                           hAppInst,              // Instance
                           NULL                    // Param
                         );

	if( !hMainWnd )
	{
		MessageBox(NULL, "CreateWindow Failed.", NULL, NULL);
		return false;
	}

	ShowWindow(hMainWnd, SW_SHOW);
	//UpdateWindow(hMainWnd);	// needed?

	return true;
}


bool DXGame::InitDirect3D()
{
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
		&device,				// Device
		&featureLevel,			// Feature Level
		&deviceContext );		// Device Context


	// Handle any device creation or DirectX version errors
	if( FAILED(hResult) )
	{
		MessageBox(NULL, "D3D11CreateDevice Failed", NULL, NULL);
		return false;
	}

	if( featureLevel != requiredFeatureLevel )
	{
		MessageBox(NULL, "Direct3D Feature Level 11 unsupported", NULL, NULL);
		return false;
	}

	// Check for 4X MSAA quality support
	HR(device->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		4,
		&msaa4xQuality));
	assert( msaa4xQuality > 0 ); // Potential problem if quality is 0
	
	// set up swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc) );
	swapChainDesc.BufferCount							= 1;
	swapChainDesc.BufferDesc.Width						= windowWidth;
	swapChainDesc.BufferDesc.Height						= windowHeight;
	swapChainDesc.BufferDesc.RefreshRate.Numerator		= 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator	= 1;
	swapChainDesc.BufferDesc.Format						= DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow							= hMainWnd;
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
	HR(device->QueryInterface(	__uuidof(IDXGIDevice),	(void**)&dxgiDevice));
	HR(dxgiDevice->GetParent(	__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));
	HR(dxgiAdapter->GetParent(	__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	// Finally make the swap chain and release the DXGI stuff
	HR(dxgiFactory->CreateSwapChain(device, &swapChainDesc, &swapChain));
	ReleaseCOMobjMacro(dxgiDevice);
	ReleaseCOMobjMacro(dxgiAdapter);
	ReleaseCOMobjMacro(dxgiFactory);

	// The remaining steps also need to happen each time the window
	// is resized, so just run the OnResize method
	OnResize();

	return true;

}

void DXGame::OnResize()
{
	
	// release old views
	ReleaseCOMobjMacro(renderTargetView);
	ReleaseCOMobjMacro(depthStencilView);
	ReleaseCOMobjMacro(depthStencilBuffer);

	// resize swap chain
	HR( swapChain->ResizeBuffers(
			1,			// BufferCount
			windowWidth,
			windowHeight,
			DXGI_FORMAT_R8G8B8A8_UNORM,	
			0)		// Swap chain flags
	);
	
	// create render target view
	ID3D11Texture2D* backBuffer;
	HR( swapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer ) );
	HR( device->CreateRenderTargetView( backBuffer, NULL, &renderTargetView ) );
	ReleaseCOMobjMacro( backBuffer );

	// Set up the description of the texture to use for the
	// depth stencil buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width			= windowWidth;
	depthStencilDesc.Height			= windowHeight;
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
	HR(device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer));
	HR(device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView));

	// Bind these views to the pipeline, so rendering actually
	// uses the underlying textures
	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	// Update the viewport and set it on the device
	viewport.TopLeftX	= 0;
	viewport.TopLeftY	= 0;
	viewport.Width		= (float)windowWidth;
	viewport.Height		= (float)windowHeight;
	viewport.MinDepth	= 0.0f;
	viewport.MaxDepth	= 1.0f;
	deviceContext->RSSetViewports(1, &viewport);

	/* OTHER STUFF WE COULD PLAY WITH */
	/* from 02_vertex_and_fragment_program.cpp */
	/*

	// Disable alpha blending
    D3D11_BLEND_DESC BlendState;
    ZeroMemory( &BlendState, sizeof( D3D11_BLEND_DESC ) );
    
    BlendState.RenderTarget[0].BlendEnable = FALSE;
    BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    
    hr = g_pDevice->CreateBlendState( &BlendState, &myBlendState_NoBlend );
    if( hr != S_OK )
        return hr;

    // Disable culling
    D3D11_RASTERIZER_DESC RSDesc;
    RSDesc.FillMode              = D3D11_FILL_SOLID;
    RSDesc.CullMode              = D3D11_CULL_NONE;
    RSDesc.FrontCounterClockwise = FALSE;
    RSDesc.DepthBias             = 0;
    RSDesc.DepthBiasClamp        = 0;
    RSDesc.SlopeScaledDepthBias  = 0;
    RSDesc.ScissorEnable         = FALSE;
    RSDesc.MultisampleEnable     = FALSE;
    RSDesc.AntialiasedLineEnable = FALSE;

    hr = g_pDevice->CreateRasterizerState( &RSDesc, &myRasterizerState_NoCull );
    if( hr != S_OK )
        return hr;
	*/
}

//--------------------------------------------------------------------------------------
// Utility function for reporting Cg errors
//--------------------------------------------------------------------------------------
void DXGame::checkForCgError( const char * situation, bool _exit )
{
    CGerror error;
    const char *string = cgGetLastErrorString(&error);

    if( error != CG_NO_ERROR ) 
    {
        if( error == CG_COMPILER_ERROR ) 
        {
            fprintf(stderr,
                "Program: %s\n"
                "Situation: %s\n"
                "Error: %s\n\n"
                "Cg compiler output...\n%s",
                "DirectX 11 and Cg Demo", situation, string,
                cgGetLastListing(myCgContext));
        } 
        else 
        {
            fprintf(stderr,
                "Program: %s\n"
                "Situation: %s\n"
                "Error: %s",
                "DirectX 11 and Cg Demo", situation, string);
        }

        if( _exit )
            exit(1);
    }
}

// Create CgContext
bool DXGame::InitCg()
{
	myCgContext = cgCreateContext();
	checkForCgError( "creating context" );

	HR(cgD3D11SetDevice( myCgContext, device ));
	checkForCgError( "setting D3D device", false );

    return true;
}


void DXGame::CleanUpCg()
{
	cgDestroyProgram( myCgVertexProgram );
    checkForCgError( "destroying vertex program" );
    cgDestroyProgram( myCgFragmentProgram );
    checkForCgError( "destroying fragment program" );
  
    cgD3D11SetDevice( myCgContext, NULL );

    cgDestroyContext( myCgContext ); 
}

LRESULT DXGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg ) 
    {
        case WM_KEYDOWN:
            switch( wParam )
            {
                case VK_ESCAPE:
                    PostQuitMessage( 0 );
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, msg, wParam, lParam );
    }

    return 0;

}