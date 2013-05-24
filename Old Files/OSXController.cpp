#include "StdAfx.h"

//
//  OSXController.cpp
//  GraphosGraphics
//
//  Created by Colden Cullen on 4/5/13.
//  Copyright (c) 2013 Colden Cullen. All rights reserved.
//

// OSX ONLY
#if defined( __APPLE__ )

#include "WindowController.h"

using namespace Graphos::Math;
using namespace Graphos::Content;
using namespace Graphos::Graphics;

bool OSXController::Initialize( void )
{
	return true;
}

void OSXController::Shutdown( void )
{
	
}

void OSXController::Resize( bool fullScreen, unsigned int newWidth, unsigned int newHeight )
{
	
}

void OSXController::Reload( void )
{
	
}

void OSXController::MessageLoop( void )
{
	
}

#endif//__APPLE__