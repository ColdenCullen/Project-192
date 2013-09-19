
#ifndef __DXGame
#define __DXGame

#include "Windows.h"
#include <d3d11.h>
#include <Cg/cg.h>
#include <Cg/cgD3D11.h>
#include <sstream>
#include <assert.h>

// Convenience macro for releasing a COM object
#ifndef ReleaseCOMobjMacro
	#define ReleaseCOMobjMacro( x ) { if( x ){  x->Release(); x = nullptr; } }
#endif

// Macro for popping up a text box based
// on a failed HRESULT and then quitting (only in debug builds)
#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)											\
	{														\
		HRESULT hr = (x);									\
		if(FAILED(hr))										\
		{													\
			MessageBox(NULL, "", "DirectX Error", MB_OK);	\
			PostQuitMessage(0);								\
		}													\
	}														
	#endif
#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif

class DXGame
{
public:
	DXGame(HINSTANCE hInstance);
	virtual ~DXGame(void);

	// the game loop
	int run();

	// Methods called by the game loop - override these in
	// derived classes to implement custom functionality
	virtual bool Init();
	virtual void OnResize(); 
	//virtual void UpdateScene(float dt)=0;
	virtual void DrawScene()=0; 
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	// Handles window, Direct3D, and Cg initialization
	bool InitMainWindow();
	bool InitDirect3D();
	bool InitCg();
	void checkForCgError( const char * situation, bool _exit = true);
	void CleanUpCg();

	//void CalculateFrameStats();

	// Window handles and such
	HINSTANCE hAppInst;
	HWND      hMainWnd;

	// Game and window state tracking
	bool      gamePaused;
	bool      minimized;
	bool      maximized;
	bool      resizing;

	// Timer for running the game on delta time
	//GameTimer timer;
	
	// DirectX related buffers, views, etc.
	UINT msaa4xQuality;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11DepthStencilView* depthStencilView;
	D3D11_VIEWPORT viewport;
	D3D_DRIVER_TYPE driverType;

	// Cg related things
	CGcontext myCgContext;
	CGprofile myCgVertexProfile;
	CGprogram myCgVertexProgram;
	CGprofile myCgFragmentProfile;
	CGprogram myCgFragmentProgram;

	// Derived class can set these in derived constructor to customize starting values.
	std::wstring windowCaption;
	int windowWidth;
	int windowHeight;
	bool enable4xMsaa;

};

#endif

