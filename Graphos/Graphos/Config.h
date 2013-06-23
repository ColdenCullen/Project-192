#ifndef _CONFIGCONTROLLER_H_
#define _CONFIGCONTROLLER_H_

#include "GraphosGame.h"
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
			void				LoadSettings( void );

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
			std::string			GetData<std::string>( std::string path );
			template<>
			const char*			GetData<const char*>( std::string path );
			template<>
			string*				GetData<string*>( std::string path );
			template<>
			GameState			GetData<GameState>( std::string path );
			template<>
			Graphos::Math::Vector3
								GetData<Graphos::Math::Vector3>( std::string path );
#endif
			#pragma endregion

			template<typename T>
			void				SetData( std::string path, T newValue )
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
			Config&				operator=( const Config& );

			Json::Value&		GetValueAtPath( std::string path );

			// JSON values
			Json::Value			config;
		};

		#pragma region GetData
#if defined( _WIN32 )
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
		string* Config::GetData<string*>( std::string path )
		{
			Json::Value& node = GetValueAtPath( path );

			if( node.isArray() )
			{
				string* toReturn = new string[ node.size() ];

				for( int ii = 0; ii < node.size(); ++ii )
					toReturn[ ii ] = node[ ii ].asString();

				return toReturn;
			}
		}
		template<>
		GameState Config::GetData<GameState>( std::string path )
		{
			const Json::Value& val = GetValueAtPath( path );

			#define ENUM_TO_STRING(enum) (#enum)

			for( int state = 0; state <= static_cast<int>( GameState::Reseting ); ++state )
			{
				string stringValue = ENUM_TO_STRING( static_cast<GameState>( state ) );

				if( val.asString() == stringValue )
					return static_cast<GameState>( state );
			}

			#undef ENUM_TO_STRING
		}
		template<>
		Graphos::Math::Vector3 Config::GetData<Graphos::Math::Vector3>( std::string path )
		{
			Json::Value root = GetValueAtPath( path );

			return Graphos::Math::Vector3(
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