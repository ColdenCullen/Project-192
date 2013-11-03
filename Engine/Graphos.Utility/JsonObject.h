#ifndef __JSON_OBJECT
#define __JSON_OBJECT

#include <json/json.h>
#include <string>

#include "Vector3.h"

namespace Graphos
{
	namespace Utility
	{
		class JsonObject
		{
		public:
								JsonObject( Json::Value obj = Json::Value( Json::objectValue ) ) : object( obj ) { }

			// Get value from settings
			template<typename T>
			T GetValue( std::string path );

			template<typename T>
			bool TryGetValue( std::string path, T& val )
			{
				if( path.size() == 0 )
					return val = object, true;

				std::string left;
				std::string right = path;
				int currentIndex;
				Json::Value* currentValue = &object;

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
			void SetValue( std::string path, T value )
			{
				GetValue<Json::Value&>( path ) = value;
			}

		private:
			Json::Value			object;

			friend class		JsonController;
		};
	}
}

#endif//__JSON_OBJECT
