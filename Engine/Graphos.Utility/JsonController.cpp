#include "JsonController.h"
#include "File.h"
#include "OutputController.h"

using namespace std;
using namespace Graphos::Utility;

void JsonController::Initialize( void )
{
	auto files = File::ScanDir( "Resources/" );

	for( auto file : files )
	{
		if( file.GetExtension() == ".json" )
		{
			auto path = file.GetLocalPath();

			// Replace /s with .s
			gInt curInd = string::npos;
			while( ( curInd = path.find( "/" ) ) != string::npos )
			{
				path = path.replace( curInd, 1, 1, '.' );
			}

			// Get path without resources and .json
			path = path.substr( 0, path.size() - 5 ).substr( 10 );

			root.Set( path, Parse( file.GetContents() ).node );
		}
	}
}

JsonObject JsonController::Parse( std::string jsonString )
{
	Json::Value toReturn;
	Json::Reader reader;

	reader.parse( jsonString, toReturn, true );

	return JsonObject( toReturn );
}

JsonObject JsonController::root;
