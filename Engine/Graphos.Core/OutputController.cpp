#include "OutputController.h"
#include "Config.h"

#include <iostream>

using namespace std;
using namespace Graphos::Core;

void OutputController::PrintMessage( OutputType type, string message )
{
	string verbosity = ISingleton<Config>::Get().GetData<string>( "Game.Verbosity" );
	if( GetWhetherPrint( type ) )
	{
		cout << GetOutputHeader( type ) << " " << message << endl;
	}
}

string OutputController::GetOutputHeader( OutputType type )
{
	switch( type )
	{
	case OutputType::OT_INFO:
		return "[INFO]   ";
	case OutputType::OT_WARNING:
		return "[WARNING]";
	case OutputType::OT_ERROR:
		return "[ERROR]  ";
	default:
		throw logic_error( "Enum type not defined in GetOutputHeader." );
	}
}

bool OutputController::GetWhetherPrint( OutputType type )
{
	string verbosity = ISingleton<Config>::Get().GetData<string>( "Game.Verbosity" );
	return
		( verbosity == "High" ) ||
		( verbosity == "Med" && type >= OutputType::OT_WARNING ) ||
		( verbosity == "Low" && type >= OutputType::OT_ERROR );
}
