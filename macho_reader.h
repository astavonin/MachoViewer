/*
 *  macho_reader.h
 *  MachoViewer
 *
 *  Created by Alexander Stavonin on 28.01.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#define MAX_ARCH_COUNT 2


#define LIST_OF_TYPE(type,name) \
struct name { \
	type *data; \
	struct name *next_ptr; \
}; \
typedef struct name name##_t;

#define ILIST_COMPARATOR(e1, e2) (e1->i - e2->i)

struct macho_section_64 {
	char sectname[16];
	char segname[16];
	uint64_t addr;
	uint64_t size;
	uint32_t offset;
	uint32_t align;
	uint32_t reloff;
	uint32_t nreloc;
	uint32_t flags;
};
typedef struct macho_section_64 macho_section_64_t;

LIST_OF_TYPE(macho_section_64_t, section_64_list);

struct macho_segment_64 {
	char segname[16];
	uint64_t vmaddr;
	uint64_t vmsize;
	uint64_t fileoff;
	uint64_t filesize;
	uint32_t nsects; 
	uint32_t flags;
	section_64_list_t *sections;
};
typedef struct macho_segment_64 macho_segment_64_t;

LIST_OF_TYPE(macho_segment_64_t, segment_64_list);

struct macho_section {
	char sectname[16];
	char segname[16];
	uint32_t addr;
	uint32_t size;
	uint32_t offset;
	uint32_t align;
	uint32_t reloff;
	uint32_t nreloc;
	uint32_t flags;
};
typedef struct macho_section macho_section_t;

LIST_OF_TYPE(macho_section_t, section_list);

struct macho_segment {
	char segname[16];
	uint32_t vmaddr;
	uint32_t vmsize;
	uint32_t fileoff;
	uint32_t filesize;
	uint32_t flags;
	uint32_t nsects; 
	section_list_t *sections;
};
typedef struct macho_segment macho_segment_t;

LIST_OF_TYPE(macho_segment_t, segment_list);

struct macho_dylib {
	char *name; 
	uint32_t timestamp; 
	uint32_t current_version; 
	uint32_t compatibility_version;
};
typedef struct macho_dylib macho_dylib_t;

LIST_OF_TYPE(macho_dylib_t, dylib_list);

struct macho_symbol {
	char *name;
	uint8_t type;
	uint8_t sect;
	uint16_t desc;
};
typedef struct macho_symbol macho_symbol_t;

LIST_OF_TYPE(macho_symbol_t, symbol_list);

struct macho_arch {
	uint32_t magic;
	cpu_type_t cputype;
	cpu_subtype_t cpusubtype;
	uint32_t offset;
	uint32_t filetype;
	uint32_t ncmds;
	uint32_t flags;
	char *dylinker;
	segment_list_t *segments;
	segment_64_list_t *segments64;
	dylib_list_t *dylibs;
	symbol_list_t *symbols;
};
typedef struct macho_arch macho_arch_t;

LIST_OF_TYPE(macho_arch_t, arch_list);

struct macho_info {
	uint32_t magic;
	int arch_count;
	arch_list_t *arch;
};
typedef struct macho_info macho_info_t;

struct macho_file {
	size_t size;
	char *begin;
	char *read_ptr;
};
typedef struct macho_file macho_file_t;

macho_info_t* open_macho_file(const char *path);
void close_macho_file(macho_info_t* macho_file);
