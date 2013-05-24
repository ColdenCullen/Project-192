//
//  OpenGLView.h
//  Graphos
//
//  Created by Colden Cullen on 5/1/13.
//  Copyright (c) 2013 Colden Cullen. All rights reserved.
//

#ifndef __OPENGLVIEW
#define __OPENGLVIEW

#import <Cocoa/Cocoa.h>
#include "TestGame.h"

@interface OpenGLView : NSOpenGLView
{

}

- (void) drawRect: (NSRect)dirtyRect;

@end

#endif//__OPENGLVIEW