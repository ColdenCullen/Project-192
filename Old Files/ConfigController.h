#ifndef _CONFIGCONTROLLER_H_
#define _CONFIGCONTROLLER_H_

#include <string>
#include <json/json.h>

using namespace std;

namespace Graphos
{
	namespace Content
	{
		class ConfigController
		{
		public:
			// Initialize the settings controller
			bool				LoadSettings( void );

			#pragma region GetData
			// Get value from settings
			template<typename T>
			T					GetData( string path ) { }
#if defined( _WIN32 )
			template<>
			int					GetData<int>( string path );
			template<>
			unsigned int		GetData<unsigned int>( string path );
			template<>
			double				GetData<double>( string path );
			template<>
			bool				GetData<bool>( string path );
			template<>
			string				GetData<string>( string path );
			template<>
			const char*			GetData<const char*>( string path );
#endif
			#pragma endregion

			static
			ConfigController&	Get( void )
			{
				static ConfigController instance;
				return instance;
			}

		private:
								ConfigController( void ) { }
								ConfigController( ConfigController& );
			void				operator=( ConfigController& );

			Json::Value			GetValueAtPath( string path );

			// JSON values
			Json::Value config;
		};

		#pragma region GetData
		template<>
		int ConfigController::GetData<int>( string path )
		{
			return GetValueAtPath( path ).asInt();
		}
		template<>
		unsigned int ConfigController::GetData<unsigned int>( string path )
		{
			return GetValueAtPath( path ).asUInt();
		}
		template<>
		double ConfigController::GetData<double>( string path )
		{
			return GetValueAtPath( path ).asDouble();
		}
		template<>
		bool ConfigController::GetData<bool>( string path )
		{
			return GetValueAtPath( path ).asBool();
		}
		template<>
		string ConfigController::GetData<string>( string path )
		{
			return GetValueAtPath( path ).asString();
		}
		template<>
		const char* ConfigController::GetData<const char*>( string path )
		{
			return GetValueAtPath( path ).asCString();
		}
		#pragma endregion
	}
}

#endif//_CONFIGCONTROLLER_H_