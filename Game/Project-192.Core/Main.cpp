#include "Game.h"

int main()
{
	// Global scope
	Graphos::Memory::Scope global();

	// Create and run game
	auto test = gnew<Project192::Game>();
	test->Run();

	// Delete game object
	delete_s( test );
}