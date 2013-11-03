#ifndef __CONFIG__CONTROLLER
#define __CONFIG__CONTROLLER

#include "JsonObject.h"
#include "JsonController.h"

#include <string>
#include <ostream>
#include <fstream>

namespace Graphos
{
	namespace Utility
	{
		class Config
		{
		public:
			// Initialize the settings controller
			static void Initialize( void )
			{
				Json() = JsonController::Get( "Config.Config" );
			}

			// Get value from settings
			template<typename T>
			static T GetData( std::string path )
			{
				return Json().GetValue<T>( path );
			}

			template<typename T>
			static void SetData( std::string path, T newValue )
			{
				Json().SetValue( path, newValue );

				//std::ofstream outfile( "Resources/Config/Config.json" );

				//outfile << config;

				//outfile.close();
			}

		private:
								Config( void ) { }
								Config( const Config& );
			Config&				operator=( const Config& );

			// JSON values
			static JsonObject& Json()
			{
				static JsonObject config;
				return config;
			}
		};
	}
}

#endif//__CONFIG__CONTROLLER