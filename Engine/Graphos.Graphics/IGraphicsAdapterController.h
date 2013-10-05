#ifndef __IGRAPHICS_ADAPTER_CONTROLLER
#define __IGRAPHICS_ADAPTER_CONTROLLER

#include "IController.h"
#include <DirectX/DirectXIncludes.h>
#include <GL/glincludes.h>


namespace Graphos
{
	namespace Graphics
	{
		class IGraphicsAdapterController : public Core::IController
		{
		protected:
			union AdapterDeviceContext
			{
				DirectX::ID3D11DeviceContext*	dxDeviceContext;
				OpenGL::GLDeviceContext			glDeviceContext;
			} deviceContext;
			union AdapterDevice
			{
				DirectX::ID3D11Device*			dxDevice;
			} device;

		public:
			virtual void		Initialize( void ) override = 0;
			virtual void		Shutdown( void ) override = 0;

			virtual void		Resize( void ) = 0;
			virtual void		Reload( void ) = 0;

			virtual void		BeginDraw( void ) = 0;
			virtual void		EndDraw( void ) = 0;
			AdapterDeviceContext&	GetDeviceContext( void ) { return deviceContext; }
			AdapterDevice&			GetDevice( void ) { return device; }
		};
	}
}

#endif//__IGRAPHICS_ADAPTER_CONTROLLER