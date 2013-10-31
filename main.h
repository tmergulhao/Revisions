#ifndef MAIN_H
#define MAIN_H

typedef enum {
	TSTMODE		= (0x1 << 0),
	CLTMODE		= (0x1 << 1),
	FILEBASE	= (0x1 << 2),
	QUIT_APP	= (0x1 << 7)
} INITMODES;

#endif
