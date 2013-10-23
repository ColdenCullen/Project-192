#include "Game.h"
#include "File.h"
#include "GraphosMemory.h"
#include "Scope.h"

#include <iostream>

using namespace std;

int main()
{
	auto scope = new Graphos::Memory::Scope();

	auto test = gnew<Project192::Game>();
	test->Run();

	delete_s( test );

	//delete scope;
	
	/*

	Graphos::Core::File test( "Herpaderp/derpderp.txt" );

	cout << test.GetFullPath() << endl;

	system( "pause" );

	/*/

	//Project192::Game game;
	//game.Run();

	//*/
}