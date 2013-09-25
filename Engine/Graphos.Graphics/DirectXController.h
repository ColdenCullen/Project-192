#if !defined( __DIRECTX_CONTROLLER ) && defined( _WIN32 )
#define __DIRECTX_CONTROLLER

#include "IGraphicsAdapterController.h"

#include <DirectX/DirectXIncludes.h>

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
			UINT				msaa4xQuality;
			ID3D11Device*		device;
			ID3D11DeviceContext* deviceContext;
			IDXGISwapChain*		swapChain;
			ID3D11Texture2D*	depthStencilBuffer;
			ID3D11RenderTargetView* renderTargetView;
			ID3D11DepthStencilView* depthStencilView;
			D3D11_VIEWPORT		viewport;
			D3D_DRIVER_TYPE		driverType;

								DirectXController( void ) { }
								DirectXController( const DirectXController& );
			DirectXController&	operator=( const DirectXController& );

			friend class		AdapterController;
		};
	}
}

#endif//__DIRECTX_CONTROLLER/_WIN32