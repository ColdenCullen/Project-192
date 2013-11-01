#ifndef __IGRAPHICS_ADAPTER_CONTROLLER
#define __IGRAPHICS_ADAPTER_CONTROLLER

namespace DirectX
{
	struct ID3D11DeviceContext;
	struct ID3D11Device;
}

struct HDC__;

namespace Graphos
{
	namespace Graphics
	{
		class IGraphicsAdapterController
		{
		protected:
			union AdapterDeviceContext
			{
				DirectX::ID3D11DeviceContext*	dxDeviceContext;
				/*OpenGL::HDC__*				glDeviceContext;*/
				HDC__*							glDeviceContext;
			} deviceContext;
			union AdapterDevice
			{
				DirectX::ID3D11Device*			dxDevice;
			} device;

		public:
			virtual void		Initialize( void ) = 0;
			virtual void		Shutdown( void ) = 0;

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