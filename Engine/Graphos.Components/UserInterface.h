#ifndef __USER_INTERFACE
#define __USER_INTERFACE

#include "Transform.h"
#include "AwesomiumView.h"
#include "Vector2.h"
#include "Mesh.h"
#include "GameObjectCollection.h"

#include <Awesomium/JSObject.h>

#define DEPTH 1.0f

namespace Graphos
{
	namespace Core
	{
		// Forward declarations
		class GraphosGame;

		class UserInterface
		{
		public:
								UserInterface( GraphosGame* owner );
								~UserInterface();

			bool				Update( void );
			void				Draw( void );
			void				KeyPress( gUInt key );

		private:
			unsigned int		width;
			unsigned int		height;

			GameObject*			uiObj;
			Mesh*				uiMesh;

			GraphosGame*		owner;

			// Awesomium view
			AwesomiumView*		view;
			Awesomium::JSObject	graphosGame;

			// GL Mesh data
			gUInt				vertexBufferObject;
			gUInt				vertexArrayObject;
			gUInt				indexBuffer;
			gUInt				numElements;

			//////////////////////////////////////////////////////////////////////////
			// JS Method Handler
			//////////////////////////////////////////////////////////////////////////
			struct JavaScriptHandler : public Awesomium::JSMethodHandler
			{
			public:
								JavaScriptHandler( UserInterface* owner ) : owner( owner ) { }

				void			OnMethodCall( Awesomium::WebView* caller, gUInt remoteObjectID, const Awesomium::WebString& methodName, const Awesomium::JSArray& args );
				Awesomium::JSValue
								OnMethodCallWithReturnValue( Awesomium::WebView* caller, gUInt remoteObjectID, const Awesomium::WebString& methodName, const Awesomium::JSArray& args );

			private:
				UserInterface*	owner;
			};
		};
	}
}

#endif//__USER_INTERFACE