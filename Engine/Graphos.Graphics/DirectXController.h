#if !defined( __DIRECTX_CONTROLLER ) && defined( _WIN32 )
#define __DIRECTX_CONTROLLER

#include "IGraphicsAdapterController.h"

#ifdef NO_NAMESPACE
#pragma message( "NO_NAMESPACE" )
#endif

#include <DirectX\DirectXIncludes.h>

namespace Graphos
{
	namespace Graphics
	{
		class DirectXController : public IGraphicsAdapterController
		{
		public:

			virtual void		Initialize( void ) override;
			virtual void		Shutdown( void ) override;
			virtual void		Resize( void );
			virtual void		Reload( void );
			virtual void		BeginDraw( void );
			virtual void		EndDraw( void );

		private:
			bool				enable4xMsaa;
			UINT				msaa4xQuality;
			
			
			DirectX::IDXGISwapChain*	swapChain;
			DirectX::ID3D11Texture2D*	depthStencilBuffer;
			DirectX::ID3D11RenderTargetView* renderTargetView;
			DirectX::ID3D11DepthStencilView* depthStencilView;
			DirectX::D3D11_VIEWPORT		viewport;
			DirectX::D3D_DRIVER_TYPE	driverType;

								DirectXController( void ) { }
								DirectXController( const DirectXController& );
			DirectXController&	operator=( const DirectXController& );

			friend class		AdapterController;
		};
	}
}

#endif//__DIRECTX_CONTROLLER/_WIN32