#include <string.h>

#include <command.h>
#include <main.h>

int main (int argc, char **argv) {
	if (argc == 2) {
		if (strcmp(argv[1], "--vanilla") == 0 ||
			strcmp(argv[1], "-v") == 0)
			USRINTERFACE::instance(CLTMODE);
		else if (	strcmp(argv[1], "--test") == 0 ||
					strcmp(argv[1], "-t") == 0)
			USRINTERFACE::instance(TSTMODE | CLTMODE);
	}
	while (true) {
		try {
			USRINTERFACE::instance()->Run();
		}
		catch (INITMODES state) {
			if (state & QUIT_APP) {
				delete USRINTERFACE::instance();
				return 0;
			}
			USRINTERFACE::instance(state);
		}
	}
}
