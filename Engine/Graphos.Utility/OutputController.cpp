#include "OutputController.h"
#include "Config.h"

#include <iostream>

#if defined( _WIN32 )
#include <Windows.h>
#endif//_WIN32

using namespace std;
using namespace Graphos::Utility;

void OutputController::PrintMessage( OutputType type, string message )
{
	if( GetWhetherPrint( type ) )
	{
		cout << GetOutputHeader( type ) << " " << message << endl;
	}
}

string OutputController::GetOutputHeader( OutputType type )
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch( type )
	{
	case OutputType::Info:
		SetConsoleTextAttribute( hConsole, 15 );
		return "[INFO]   ";
	case OutputType::Warning:
		SetConsoleTextAttribute( hConsole, 14 );
		return "[WARNING]";
	case OutputType::Error:
		SetConsoleTextAttribute( hConsole, 12 );
		return "[ERROR]  ";
	default:
		throw logic_error( "Enum type not defined in GetOutputHeader." );
	}
}

bool OutputController::GetWhetherPrint( OutputType type )
{
	string verbosity = Config::GetData<string>( "Game.Verbosity" );
	return
		( verbosity == "High" ) ||
		( verbosity == "Med" && type >= OutputType::Warning ) ||
		( verbosity == "Low" && type >= OutputType::Error ) ||
		( verbosity == "" );
}
