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
			void				KeyPress( unsigned int key );

		private:
			// GL Texture ID
			//unsigned int		textureID;

			unsigned int		width;
			unsigned int		height;

			//Mesh				uiMesh();
			GameObjectCollection
								objects;
			GameObject*			uiMesh;

			Math::Transform		transform;

			GraphosGame*		owner;

			// Awesomium view
			AwesomiumView*		view;
			Awesomium::JSObject	graphosGame;

			// GL Mesh data
			unsigned int		vertexBufferObject;
			unsigned int		vertexArrayObject;
			unsigned int		indexBuffer;
			unsigned int		numElements;

			//////////////////////////////////////////////////////////////////////////
			// JS Method Handler
			//////////////////////////////////////////////////////////////////////////
			struct JavaScriptHandler : public Awesomium::JSMethodHandler
			{
			public:
								JavaScriptHandler( UserInterface* owner ) : owner( owner ) { }

				void			OnMethodCall( Awesomium::WebView* caller, unsigned int remoteObjectID, const Awesomium::WebString& methodName, const Awesomium::JSArray& args );
				Awesomium::JSValue
								OnMethodCallWithReturnValue( Awesomium::WebView* caller, unsigned int remoteObjectID, const Awesomium::WebString& methodName, const Awesomium::JSArray& args );

			private:
				UserInterface*	owner;
			};
		};
	}
}

#endif//__USER_INTERFACE