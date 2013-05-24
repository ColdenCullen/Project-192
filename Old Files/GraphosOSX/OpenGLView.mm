//
//  OpenGLView.m
//  Graphos
//
//  Created by Colden Cullen on 5/1/13.
//  Copyright (c) 2013 Colden Cullen. All rights reserved.
//

#import "OpenGLView.h"
//#include <OpenGL/gl.h>

@implementation OpenGLView

- (id)initWithFrame: (NSRect)frame
{
    self = [super initWithFrame: frame];
    if( self )
	{
		Graphos::TestGame game;
		game.Run();
    }
    
    return self;
}

- (void)drawRect: (NSRect)dirtyRect
{
	/*
    // Drawing code here.
	glClearColor( 0, 0, 0, 0 );
    glClear( GL_COLOR_BUFFER_BIT );
    drawAnObject();
    glSwapAPPLE();
	//*/
}

static void drawAnObject ()
{
	/*
    glColor3f( 1.0f, 0.85f, 0.35f );
    glBegin( GL_TRIANGLES );
    {
        glVertex3f(  0.0,  0.6, 0.0 );
        glVertex3f( -0.2, -0.3, 0.0 );
        glVertex3f(  0.2, -0.3, 0.0 );
    }
    glEnd();
	//*/
}

@end
