#ifndef __JSON_CONTROLLER
#define __JSON_CONTROLLER

#include "JsonObject.h"

namespace Graphos
{
	namespace Utility
	{
		class JsonController
		{
		public:
			static void			Initialize( void );

			static JsonObject	Get( std::string path )						{ return root.Get<JsonObject>( path ); }
			static bool			TryGet( std::string path, JsonObject& val )	{ return root.TryGet( path, val ); }

			static JsonObject	Parse( std::string jsonString );

		private:
			static JsonObject	root;
		};
	}
}

#endif//__JSON_CONTROLLER
