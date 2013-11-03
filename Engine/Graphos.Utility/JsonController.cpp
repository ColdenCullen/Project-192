#include "JsonController.h"
#include "File.h"
#include "OutputController.h"

using namespace Graphos::Utility;

void JsonController::Initialize( void )
{
	auto files = File::ScanDir( "Resources/" );

	for( auto file : files )
	{
		if( file.GetExtension() == ".json" )
		{
			
		}
	}
}
