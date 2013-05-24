#include "ConfigController.h"

#define _USE_READ_FILE
#include <Helpers.h>

#define CONFIG_PATH "Resources/Config/Config.json"

using namespace std;
using namespace Graphos::Content;

bool ConfigController::LoadSettings( void )
{
	Json::Reader reader;

	if( !reader.parse( Helpers::ReadFile( CONFIG_PATH ), config ) )
		return false;

	return true;
}

Json::Value ConfigController::GetValueAtPath( string path )
{
	string left;
	string right = path;
	int currentIndex;
	Json::Value currentValue = config;

	do
	{
		currentIndex = right.find( '.' );

		if( currentIndex != string::npos )
		{
			left = right.substr( 0, currentIndex );
			right = right.substr( currentIndex + 1, string::npos );
		}
		else
		{
			left = right;
		}

		currentValue = currentValue.get( left, currentValue );
	} while( currentIndex != string::npos );

	return currentValue;
}