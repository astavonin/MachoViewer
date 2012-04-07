//
//  MachoViewerAppDelegate.h
//  MachoViewer
//
//  Created by Alexander Stavonin on 28.01.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class MachOReader;

#if (MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_5)
@interface MachoViewerAppDelegate : NSObject
#else
@interface MachoViewerAppDelegate : NSObject <NSApplicationDelegate>
#endif
{
	NSPoint lastTopLeft;
}

-(IBAction) onOpen:(id)sender;

-(void)openFileWithString:(NSString*)path;

@end
