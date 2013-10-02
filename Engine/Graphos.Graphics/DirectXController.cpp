#include "stdafx.h"
#include "DirectXController.h"

using namespace Graphos::Graphics;

void DirectXController::Initialize( void )
{
	driverType = D3D_DRIVER_TYPE_HARDWARE;
	//enable4xMsaa = false;
	//msaa4xQuality = 0;

	device = nullptr;
	deviceContext = nullptr;
	swapChain = nullptr;
	depthStencilBuffer = nullptr;
	renderTargetView = nullptr;
	depthStencilView = nullptr;
	ZeroMemory( &viewport, sizeof(D3D11_VIEWPORT) );
}

void DirectXController::Shutdown( void )
{
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

void DirectXController::Resize( void )
{
	
}

void DirectXController::Reload( void )
{
	
}

void DirectXController::BeginDraw( void )
{
	
}

void DirectXController::EndDraw( void )
{
	
}
