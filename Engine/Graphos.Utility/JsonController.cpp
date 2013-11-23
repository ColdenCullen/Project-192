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

			string fileName = file.GetFileName().substr( 0, file.GetFileName().size() - 5 );

			root.Set( path + fileName, Parse( file.GetContents() ).node );
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
