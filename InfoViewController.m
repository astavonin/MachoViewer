//
//  InfoViewController.m
//  MachoViewer
//
//  Created by Alexander Stavonin on 02.02.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "InfoViewController.h"


@implementation InfoViewController

@synthesize reader;
@synthesize topLeft;

+(InfoViewController*)infoViewController:(MachOReader*)reader
{
	InfoViewController *controller = [[InfoViewController alloc] init];
	controller.reader = reader;
	
	return controller;
}

- (void)pathControlDoubleClick:(id)sender
{
//    if ([pathControl clickedPathComponentCell] != nil)
//        [[NSWorkspace sharedWorkspace] openURL:[[pathControl clickedPathComponentCell] URL]];
}

-(void)awakeFromNib
{
	topLeft = [window cascadeTopLeftFromPoint:topLeft];
	[window setFrameTopLeftPoint:topLeft];
	[window makeKeyAndOrderFront:nil];
}

-(void) windowWillClose:(NSNotification *)notification 
{
	[self release];
}

-(void)dealloc
{
	[reader release];
	[super dealloc];
}

@end
