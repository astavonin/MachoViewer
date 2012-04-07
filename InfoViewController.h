//
//  InfoViewController.h
//  MachoViewer
//
//  Created by Alexander Stavonin on 02.02.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class MachOReader;

@interface InfoViewController : NSObject 
{
	MachOReader *reader;
	NSPoint topLeft;

	IBOutlet NSWindow *window;
}

@property (retain) MachOReader *reader;
@property (assign) NSPoint topLeft;

+(InfoViewController*)infoViewController:(MachOReader*)reader;
-(void)pathControlDoubleClick:(id)sender;

@end
