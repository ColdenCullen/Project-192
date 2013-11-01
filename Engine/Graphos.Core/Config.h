#ifndef _CONFIGCONTROLLER_H_
#define _CONFIGCONTROLLER_H_

#include "Vector3.h"

#include <string>
#include <ostream>
#include <fstream>
#include <json/json.h>

namespace Graphos
{
	namespace Core
	{
		class Config
		{
		public:
			// Initialize the settings controller
			static void			Initialize( void );

			#pragma region GetData
			// Get value from settings
			template<typename T>
			static T			GetData( std::string path );
#if 0//defined( _WIN32 )
			template<>
			static int			GetData<int>( std::string path );
			template<>
			static unsigned int	GetData<unsigned int>( std::string path );
			template<>
			static float		GetData<float>( std::string path );
			template<>
			static bool			GetData<bool>( std::string path );
			template<>
			static std::string	GetData<std::string>( std::string path );
			template<>
			static const char*	GetData<const char*>( std::string path );
			template<>
			static std::string*	GetData<std::string*>( std::string path );
			template<>
			static Math::Vector3
								GetData<Math::Vector3>( std::string path );
#endif
			#pragma endregion

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

		#pragma region GetData
#if 0//defined( _WIN32 )
		template<>
		int Config::GetData<int>( std::string path )
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
		unsigned int Config::GetData<unsigned int>( std::string path )
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
		float Config::GetData<float>( std::string path )
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
		bool Config::GetData<bool>( std::string path )
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
		std::string Config::GetData<std::string>( std::string path )
		{
			return GetValueAtPath( path ).asString();
		}
		template<>
		const char* Config::GetData<const char*>( std::string path )
		{
			return GetValueAtPath( path ).asCString();
		}
		template<>
		std::string* Config::GetData<std::string*>( std::string path )
		{
			Json::Value& node = GetValueAtPath( path );

			if( node.isArray() )
			{
				std::string* toReturn = new std::string[ node.size() ];

				for( unsigned int ii = 0; ii < node.size(); ++ii )
					toReturn[ ii ] = node[ ii ].asString();

				return toReturn;
			}
		}
		template<>
		Math::Vector3 Config::GetData<Math::Vector3>( std::string path )
		{
			Json::Value root = GetValueAtPath( path );

			return Math::Vector3(
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