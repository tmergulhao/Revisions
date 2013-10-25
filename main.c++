#include <sqlite3.h>
#include <string.h>

#include "command.h"

int main (int argc, char **argv) {
	class MethaUI * Interface;
	
	if (argc == 2) {
		if (strcmp(argv[1], "--vanilla") == 0 || strcmp(argv[1], "-v") == 0)
			Interface = new CLTUI;
			// implement --vanilla for stubs STD
		else if (strcmp(argv[1], "--filebase") == 0 || strcmp(argv[1], "-f") == 0) {}
			// implement --filebase
		else if (strcmp(argv[1], "--sqlite3") == 0 || strcmp(argv[1], "-f") == 0) {}
			// implement --sqlite3
		
	} else Interface = new CLTUI;
	
	Interface->Run();
	
	return 0;
}
