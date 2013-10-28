#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <sqlite3.h>

#include "basetypes.h"

class SQLInterface {
		static SQLInterface * p_instance;
	public:
		// USER
		// VALIDATE DEVELOPER LOGIN
		virtual bool Login (Developer *) = 0;
		
		SQLInterface() {}
		SQLInterface(int);
		
		static SQLInterface * instance (int);
		static SQLInterface * instance () {
			return p_instance;
		}
};

#endif
