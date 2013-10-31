#ifndef __GRAPHICS_CONTROLLER
#define __GRAPHICS_CONTROLLER

namespace Graphos
{
	namespace Graphics
	{
		enum class				GraphicsAdapter { OpenGL, DirectX };

		class GraphicsController
		{
		public:
			static void			Initialize( void );
			static void			Shutdown( void );
			static void			Resize( void );
			static void			Reload( void );

			static GraphicsAdapter	
								GetActiveAdapter( void ) { return activeAdapter; }
			static void			MessageLoop( void );

		private:
			static GraphicsAdapter	
								activeAdapter;

								GraphicsController( void ) { }
								GraphicsController( const GraphicsController& );
			void				operator=( const GraphicsController& );

			static void			UpdateGraphicsAdapter( void );
		};
	}
}

#endif//__GRAPHICS_CONTROLLER
