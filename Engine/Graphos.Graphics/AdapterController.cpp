#include "stdafx.h"
#include "AdapterController.h"
#include "DirectXController.h"
#include "OpenGlController.h"
#include "GraphicsController.h"

using namespace Graphos::Graphics;

IGraphicsAdapterController* AdapterController::Get( void )
{
	static OpenGlController glInstance;
	static DirectXController dxInstance;

	if( Core::ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::OpenGL )
	{
		return &glInstance;
	}
#ifdef _WIN32
	else if( Core::ISingleton<GraphicsController>::Get().GetActiveAdapter() == GraphicsAdapter::DirectX )
	{
		return &dxInstance;
	}
#endif//_WIN32
	return nullptr;
}
