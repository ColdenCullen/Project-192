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

			/**
			 * @fn	bool UserInterface::Update( void );
			 *
			 * @brief	Updates the mouse position and click status.
			 *
			 * @author	Colden Cullen
			 *
			 * @return	true if it succeeds, false if it fails.
			 */
			bool				Update( void );
			void				Draw( void );
			void				KeyPress( gUInt key );

		private:
			float				width;
			float				height;

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

				/**
				 * @fn	void OnMethodCall( Awesomium::WebView* caller, gUInt remoteObjectID,
				 * 		const Awesomium::WebString& methodName, const Awesomium::JSArray& args );
				 *
				 * @brief	Handles Javascript function calls.
				 *
				 * @author	Colden Cullen
				 *
				 * @param [in,out]	caller	If non-null, the caller.
				 * @param	remoteObjectID	Identifier for the remote object.
				 * @param	methodName	  	Name of the method.
				 * @param	args		  	The arguments.
				 */
				void			OnMethodCall(	Awesomium::WebView* caller, 
												gUInt remoteObjectID, 
												const Awesomium::WebString& methodName, 
												const Awesomium::JSArray& args );

				/**
				 * @fn	Awesomium::JSValue OnMethodCallWithReturnValue( Awesomium::WebView* caller,
				 * 		gUInt remoteObjectID, const Awesomium::WebString& methodName,
				 * 		const Awesomium::JSArray& args );
				 *
				 * @brief	A Javascript function call that allows us to return a variable to JS.
				 *
				 * @author	Colden Cullen
				 *
				 * @param [in,out]	caller	If non-null, the caller.
				 * @param	remoteObjectID	Identifier for the remote object.
				 * @param	methodName	  	Name of the method.
				 * @param	args		  	The arguments.
				 *
				 * @return	Data for the Javascript.
				 */

				Awesomium::JSValue
								OnMethodCallWithReturnValue(	Awesomium::WebView* caller, 
																gUInt remoteObjectID, 
																const Awesomium::WebString& methodName, 
																const Awesomium::JSArray& args );

			private:
				UserInterface*	owner;
			};
		};
	}
}

#endif//__USER_INTERFACE