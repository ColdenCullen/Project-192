/**
 * @file	JsonController.h
 *
 * @brief	Declares the JSON controller class.
 */

#ifndef __JSON_CONTROLLER
#define __JSON_CONTROLLER

#include "JsonObject.h"

namespace Graphos
{
	namespace Utility
	{
		/**
		 * @class	JsonController
		 *
		 * @brief	A controller for handling JSON Objects.
		 *
		 * @author	Colden Cullen
		 */
		class JsonController
		{
		public:
			static void			Initialize( void );

			/**
			 * @fn	static JsonObject JsonController::Get( std::string path )
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
			static JsonObject	Get( std::string path )						{ return root.Get<JsonObject>( path ); }

			/**
			 * @fn	static bool JsonController::TryGet( std::string path, JsonObject& val )
			 *
			 * @brief	Gets the children of this JSON Object.
			 *
			 * @author	Colden Cullen
			 *
			 * @return	The children.
			 */
			static bool			TryGet( std::string path, JsonObject& val )	{ return root.TryGet( path, val ); }

			/**
			 * @fn	static JsonObject JsonController::Parse( std::string jsonString );
			 *
			 * @brief	Parses the given JSON string.
			 *
			 * @author	Colden Cullen
			 *
			 * @param	jsonString	The JSON string to parse.
			 *
			 * @return	The resulting JsonObject.
			 */
			static JsonObject	Parse( std::string jsonString );

		private:

			/**
			 * @brief	The root.
			 */
			static JsonObject	root;
		};
	}
}

#endif//__JSON_CONTROLLER
