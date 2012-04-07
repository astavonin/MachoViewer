//
//  MachoViewerAppDelegate.m
//  MachoViewer
//
//  Created by Alexander Stavonin on 28.01.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "MachOReader.h"
#import "InfoViewController.h"

#import "MachoViewerAppDelegate.h"

@implementation MachoViewerAppDelegate


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification 
{
}

-(BOOL)application: (NSApplication *) app openFile: (NSString *) filename 
{
	[self openFileWithString:filename];
	
	return YES;
}

-(IBAction) onOpen:(id)sender 
{	
    int result;
    NSOpenPanel *oPanel = [NSOpenPanel openPanel];

    result = [oPanel runModalForDirectory:NSHomeDirectory()
									 file:nil types:nil];
    if (result == NSOKButton) {
		
		NSArray *filesToOpen = [oPanel URLs];
		NSURL *url = [filesToOpen objectAtIndex:0];
		[self openFileWithString:[url path]];
	}
}

-(void)openFileWithString:(NSString*)path 
{
	MachOReader *reader;
	InfoViewController *controller;

	reader = [[MachOReader alloc] init];
	controller = [InfoViewController infoViewController:reader];
	controller.topLeft = lastTopLeft;

	if ([reader openMachOFile:path] != YES) {
		NSAlert *alert = [[[NSAlert alloc] init] autorelease];
		[alert setIcon:[NSImage imageNamed:@"warning.icns"]];
		[alert addButtonWithTitle:@"OK"];
		[alert setMessageText:@"Cann't open file."];
		[alert setInformativeText:[NSString stringWithFormat:@"Invalid file format.\n(%@)", path]];
		[alert setAlertStyle:NSWarningAlertStyle];
		[alert beginSheetModalForWindow:nil modalDelegate:self 
						 didEndSelector:@selector(alertDidEnd:returnCode:contextInfo:) contextInfo:nil];
		return;
	}
	[NSBundle loadNibNamed:@"InfoView" owner:controller];
	lastTopLeft = controller.topLeft;
	[reader release];
}

-(void)alertDidEnd:(NSAlert *)alert returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo
{
}

- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
{
    return NO;
}

-(void)dealloc
{
	[super dealloc];
}

@end
