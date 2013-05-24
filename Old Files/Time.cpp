#include "Time.h"

#ifdef _DEBUG
#include <iostream>
using namespace std;
#endif//_DEBUG

using namespace Graphos;

void Time::Update( void )
{
	prev = cur;
	cur = clock();

	deltaTime = static_cast<float>( cur - prev ) / CLOCKS_PER_SEC;
	totalTime += deltaTime;

	// Update framerate
#ifdef _DEBUG
	secondTime + deltaTime;
	++frameCount;

	if( secondTime >= 1.0f )
	{
		cout << frameCount << endl;
		secondTime = 0.0f;
		frameCount = 0;
	}
#endif//_DEBUG
}