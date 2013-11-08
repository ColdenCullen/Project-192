#ifndef __JSON_OBJECT
#define __JSON_OBJECT

#include <json/json.h>
#include <string>
#include <vector>

#include "Vector3.h"

namespace Graphos
{
	namespace Utility
	{
		class JsonObject
		{
		public:
			JsonObject( Json::Value obj = Json::Value( Json::objectValue ) ) : node( obj ) { }

			// Get value from settings
			template<typename T>
			T Get( std::string path );

			std::vector<JsonObject> GetChildren( void );

			template<typename T>
			bool TryGet( std::string path, T& val )
			{
				if( path.size() == 0 )
					return val = node, true;

				std::string left;
				std::string right = path;
				int currentIndex;
				Json::Value* currentValue = &node;

				do
				{
					currentIndex = right.find( '.' );

					if( currentIndex != std::string::npos )
					{
						left = right.substr( 0, currentIndex );
						right = right.substr( currentIndex + 1, std::string::npos );
					}
					else
					{
						left = right;
					}

					currentValue = &( *currentValue )[ left ];

					if( currentValue->isNull() )
						return val = Json::Value::null, false;
				} while( currentIndex != std::string::npos );

				return val = *currentValue, true;
			}

			template<typename T>
			void Set( std::string path, T value )
			{
				Get<Json::Value&>( path ) = value;
			}

			Json::Value			node;
		};
	}
}

#endif//__JSON_OBJECT
