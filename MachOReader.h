//
//  MachOReader.h
//  MachoViewer
//
//  Created by Alexander Stavonin on 28.01.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "macho_reader.h"

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////  Data representation  //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

@interface MachODyLib : NSObject
{
	NSURL *pathName;
	NSString *name;
	NSNumber *timestamp; 
	NSNumber *current_version; 
	NSNumber *compatibility_version;	
}

@property (readonly) NSURL *pathName;
@property (readonly) NSString *name;
@property (readonly) NSNumber *timestamp; 
@property (readonly) NSNumber *current_version; 
@property (readonly) NSNumber *compatibility_version;	

-(id)initWithDylib:(macho_dylib_t*)data;

@end

@interface MachOSymbol : NSObject
{
	NSString *name;
	NSNumber *type;
	uint8 sect;
	uint16 desc;
}

@property (readonly) NSString *name;
@property (readonly) NSNumber *type;
@property (readonly) uint8 sect;
@property (readonly) uint16 desc;

-(id)initWithSymbol:(macho_symbol_t*)data;

@end

@interface MachOSection : NSObject
{
	NSString *sectname;
	NSString *segname;
	uint addr;
	uint size;
	uint offset;
	uint align;
	uint reloff;
	uint nreloc;
	uint flags;
	NSString *asString;

	NSArray *sections; // fake!!!
}

@property (readonly) NSArray *sections;
@property (readonly) NSString *asString;

@property (readonly) NSString *sectname;
@property (readonly) NSString *segname;
@property (readonly) uint addr;
@property (readonly) uint size;
@property (readonly) uint offset;
@property (readonly) uint align;
@property (readonly) uint reloff;
@property (readonly) uint nreloc;
@property (readonly) uint flags;	

-(id)initWithSection:(macho_section_t*)data;
-(id)initWithSection64:(macho_section_64_t*)data;

-(void)buildInfoString;

@end

@interface MachOSegment : NSObject
{
	NSString *segname;
	uint vmaddr;
	uint vmsize;
	uint fileoff;
	uint filesize;
	uint flags;
	uint nsects; 
	NSMutableArray *sections;
	
	NSString *asString;
}

@property (readonly) NSString *asString;
@property (readonly) NSString *segname;
@property (readonly) uint vmaddr;
@property (readonly) uint vmsize;
@property (readonly) uint fileoff;
@property (readonly) uint filesize;
@property (readonly) uint flags;
@property (readonly) uint nsects;
@property (readonly) NSMutableArray *sections;

-(id)initWithSegment:(macho_segment_t*)data;
-(id)initWithSegment64:(macho_segment_64_t*)data;
-(void)buildInfoString;

@end

@interface StringFormatter : NSObject
{
	NSDictionary *boldFont;
	NSDictionary *normalFont;
	NSMutableAttributedString *resultString;
}

@property (readonly) NSMutableAttributedString *resultString;

-(void)addString:(NSString*)data withName:(NSString*)name;
-(void)addUInt:(uint)data withName:(NSString*)name;

@end


@interface MachOArch : NSObject
{
	NSNumber *magic;
	NSNumber *cputype;
	NSNumber *cpusubtype;
	NSNumber *offset;
	NSNumber *filetype;
	NSNumber *ncmds;
	NSNumber *flags;
	NSURL *dylinker;
	NSNumber *nseg;
	NSMutableArray *segments;
	NSMutableArray *dylibs;
	NSMutableArray *symbols;
}

@property (readonly) NSNumber *nseg;
@property (readonly) NSNumber *magic;
@property (readonly) NSNumber *cputype;
@property (readonly) NSNumber *cpusubtype;
@property (readonly) NSNumber *offset;
@property (readonly) NSNumber *filetype;
@property (readonly) NSNumber *ncmds;
@property (readonly) NSNumber *flags;
@property (readonly) NSURL *dylinker;
@property (readonly) NSMutableArray *segments;
@property (readonly) NSMutableArray *dylibs;
@property (readonly) NSMutableArray *symbols;

-(id)initWithArch:(macho_arch_t*)data;

@end

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////   Reader   /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

@interface MachOReader : NSObject {
	macho_info_t *machoInfo;
	NSString *binaryName;
	NSURL *binaryPath;
	NSMutableArray *archs;
}

@property (readonly) NSString *binaryName;
@property (readonly) NSURL *binaryPath;
@property (retain) NSMutableArray *archs;

-(BOOL)openMachOFile:(NSString*)path;
-(void)closeMachOFile;

@end


////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  Transformers  /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

@interface ArchListToNamesTransformer : NSObject 
{}
@end

@interface ArchToNameTransformer : NSObject 
{}
@end

@interface DecToHexTransformer : NSObject 
{}
@end

@interface FileTypeTransformer : NSObject 
{}
@end

@interface ArchFlagsTransformer : NSObject 
{}
@end

@interface SymbFlagsTransformer : NSObject 
{}
@end
