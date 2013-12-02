// C++ Libs
///////////
#include <stdexcept>
#include <iostream>
using namespace std;

// ANSI C Libs
//////////////
#include <string.h>

// Local Libs
/////////////
#include <command.h>
#include <main.h>

#define	ctab	"\t"

int main (int argc, char **argv) {
	try {
		if (argc == 2) {
			if (strcmp(argv[1], "vanilla") == 0)
				USRINTERFACE::instance(CLTMODE);
			else if (strcmp(argv[1], "test") == 0)
				USRINTERFACE::instance(TSTMODE | CLTMODE);
		}
	}
	catch (INITMODES state) {
		if (state & QUIT_APP) {
			delete USRINTERFACE::instance();
			return 0;
		}
		USRINTERFACE::instance(state);
	}
	catch (invalid_argument error) {
		cout << ctab << error.what();
		getchar();
		return 0;
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
		catch (invalid_argument error) {
			cout << ctab << error.what();
			delete USRINTERFACE::instance();
		}
	}
}
