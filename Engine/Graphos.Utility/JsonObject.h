/**
 * @file	JsonObject.h
 *
 * @brief	Declares the JSON object class.
 */

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
		/**
		 * @class	JsonObject
		 *
		 * @brief	A JSON object.
		 *
		 * @author	Colden Cullen
		 */
		class JsonObject
		{
		public:
			/**
			 * @fn	explicit JsonObject::JsonObject( Json::Value obj = Json::Value( Json::objectValue ) )
			 *
			 * @brief	Constructor.
			 *
			 * @author	Colden Cullen
			 *
			 * @param	obj	(Optional) the object.
			 */
			explicit JsonObject( Json::Value obj = Json::Value( Json::objectValue ) ) : node( obj ) { }

			/**
			 * @fn	template<typename T> T JsonObject::Get( std::string path );
			 *
			 * @brief	Gets the given file.
			 *
			 * @author	Colden Cullen
			 *
			 * @tparam	typename T	Type of the typename t.
			 * @param	path	Full pathname of the value.
			 *
			 * @return	The value found.
			 */
			template<typename T>
			T Get( std::string path );

			/**
			 * @fn	std::vector<JsonObject> JsonObject::GetChildren( void );
			 *
			 * @brief	Gets the children of this JSON Object.
			 *
			 * @author	Colden Cullen
			 *
			 * @return	The children.
			 */
			std::vector<JsonObject> GetChildren( void );

			/**
			 * @fn	bool JsonObject::TryGet( std::string path, T& val )
			 *
			 * @brief	Attempts to get from the given path.
			 *
			 * @author	Colden Cullen
			 *
			 * @param	path	   	Full pathname of the value.
			 * @param [out]	val		The value.
			 *
			 * @return	true if it succeeds, false if it fails.
			 */
			template<typename T>
			bool TryGet( std::string path, T& val )
			{
				if( path.size() == 0 )
					return val = JsonObject( node ).Get<T>( "" ), true;

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
						return val = T(), false;
				} while( currentIndex != std::string::npos );

				return val = JsonObject( *currentValue ).Get<T>( "" ), true;
			}

			/**
			 * @fn	void JsonObject::Set( std::string path, T value )
			 *
			 * @brief	Sets the given file.
			 *
			 * @author	Colden Cullen
			 *
			 * @param	path 	Full pathname of the file.
			 * @param	value	The value.
			 */
			template<typename T>
			void Set( std::string path, T value )
			{
				Get<Json::Value&>( path ) = value;
			}

			/**
			 * @brief	The node.
			 */
			Json::Value			node;
		};
	}
}

#endif//__JSON_OBJECT
