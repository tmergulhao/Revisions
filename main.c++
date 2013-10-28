#include <string.h>

#include "command.h"
#include "main.h"

int main (int argc, char **argv) {
	if (argc == 2) {
		if (strcmp(argv[1], "--vanilla") == 0 || strcmp(argv[1], "-v") == 0)
			MethaUI::instance(CLTMODE | STUBEBASE);
			// implement --vanilla for stubs STD
	}
	else
		MethaUI::instance(CLTMODE | STUBEBASE);
	
	MethaUI::instance()->Run();
	// CHECK DEALOCCATION OF ASSETS
	
	return 0;
}
