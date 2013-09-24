#ifndef __GRAPHICS_CONTROLLER
#define __GRAPHICS_CONTROLLER

#include "IController.h"
#include "ISingleton.h"

namespace Graphos
{
	namespace Graphics
	{
		enum class				GraphicsAdapter { OpenGL, DirectX };

		class GraphicsController : public Core::IController
		{
		public:
			void				Initialize( void ) override;
			//TODO: Should probably implement this
			void				Shutdown( void ) override { }
			// Resizes display with given values
			void				Resize( void );
			// Reloads display based on config settings
			void				Reload( void );

			GraphicsAdapter		GetActiveAdapter( void ) const { return activeAdapter; }

			void				MessageLoop( void );

		private:
			GraphicsAdapter		activeAdapter;

								GraphicsController( void ) { }
								GraphicsController( const GraphicsController& );
			void				operator=( const GraphicsController& );

			void				UpdateGraphicsAdapter( void );

			friend class		Core::ISingleton<GraphicsController>;
		};
	}
}

#endif//__GRAPHICS_CONTROLLER
