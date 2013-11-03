#ifndef __CONFIG__CONTROLLER
#define __CONFIG__CONTROLLER

#include "Vector3.h"

#include <string>
#include <ostream>
#include <fstream>
#include <json/json.h>

namespace Graphos
{
	namespace Utility
	{
		class Config
		{
		public:
			// Initialize the settings controller
			static void			Initialize( void );

			// Get value from settings
			template<typename T>
			static T			GetData( std::string path );

			template<typename T>
			static void			SetData( std::string path, T newValue )
			{
				GetValueAtPath( path ) = newValue;

				std::ofstream outfile( "Resources/Config/Config.json" );

				outfile << config;

				outfile.close();
			}

		private:
								Config( void ) { }
								Config( const Config& );
			Config&				operator=( const Config& );

			static Json::Value&	GetValueAtPath( std::string path );

			// JSON values
			static Json::Value	config;
		};
	}
}

#endif//__CONFIG__CONTROLLER