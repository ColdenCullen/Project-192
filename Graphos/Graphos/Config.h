#ifndef _CONFIGCONTROLLER_H_
#define _CONFIGCONTROLLER_H_

#include <string>
#include <ostream>
#include <fstream>
#include <json/json.h>

#include "Vector3.h"

using namespace Graphos::Math;

namespace Graphos
{
	namespace Core
	{
		class Config
		{
		public:
			// Initialize the settings controller
			bool				LoadSettings( void );

			#pragma region GetData
			// Get value from settings
			template<typename T>
			T					GetData( std::string path );
#if defined( _WIN32 )
			template<>
			int					GetData<int>( std::string path );
			template<>
			unsigned int		GetData<unsigned int>( std::string path );
			template<>
			float				GetData<float>( std::string path );
			template<>
			bool				GetData<bool>( std::string path );
			template<>
			string				GetData<string>( std::string path );
			template<>
			const char*			GetData<const char*>( std::string path );
			template<>
			Vector3				GetData<Vector3>( std::string path );
#endif
			#pragma endregion

			template<typename T>
			void				SetData( string path, T newValue )
			{
				GetValueAtPath( path ) = newValue;

				std::ofstream outfile( "Resources/Config/Config.json" );

				outfile << config;

				outfile.close();
			}

			static Config&		Get( void )
			{
				static Config instance;
				return instance;
			}

		private:
								Config( void ) { }
								Config( const Config& );
			void				operator=( const Config& );

			Json::Value&		GetValueAtPath( std::string path );

			// JSON values
			Json::Value			config;
		};

		#pragma region GetData
#if defined( _WIN32 )
		template<>
		int Config::GetData<int>( string path )
		{
			const Json::Value& val = GetValueAtPath( path );

			if( val.isInt() )
			{
				return val.asInt();
			}
			else
			{
				return atoi( val.asCString() );
			}
		}
		template<>
		unsigned int Config::GetData<unsigned int>( string path )
		{
			const Json::Value& val = GetValueAtPath( path );

			if( val.isInt() )
			{
				return val.asUInt();
			}
			else
			{
				return static_cast<unsigned int>( atoi( val.asCString() ) );
			}
		}
		template<>
		float Config::GetData<float>( string path )
		{
			const Json::Value& val = GetValueAtPath( path );

			if( val.isInt() )
			{
				return static_cast<float>( val.asInt() );
			}
			else if( val.isDouble() )
			{
				return static_cast<float>( val.asDouble() );
			}
			else
			{
				return static_cast<float>( atof( val.asCString() ) );
			}
		}
		template<>
		bool Config::GetData<bool>( string path )
		{
			const Json::Value& val = GetValueAtPath( path );

			if( val.isUInt() )
			{
				return val.asBool();
			}
			else
			{
				return val.asString() == "true";
			}
		}
		template<>
		string Config::GetData<string>( string path )
		{
			return GetValueAtPath( path ).asString();
		}
		template<>
		const char* Config::GetData<const char*>( string path )
		{
			return GetValueAtPath( path ).asCString();
		}
		template<>
		Vector3	Config::GetData<Vector3>( string path )
		{
			Json::Value root = GetValueAtPath( path );

			return Vector3(
				static_cast<float>( root.get( "x", root ).asDouble() ),
				static_cast<float>( root.get( "y", root ).asDouble() ),
				static_cast<float>( root.get( "z", root ).asDouble() )
			);
		}
#endif
		#pragma endregion
	}
}

#endif//_CONFIGCONTROLLER_H_