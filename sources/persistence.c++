#include <string.h>

#include "persistence.h"
#include "main.h"

// SQLITE INTERFACE
///////////////////

class SQLiteBase: public SQLInterface {
	private:
	public:
		bool Login (Developer *);
		SQLiteBase () {
	
		}
};

bool SQLiteBase::Login (Developer * developer) { return true; }

// SINGLETON STATEMENTS
///////////////////////

SQLInterface * SQLInterface::p_instance = 0;

SQLInterface * SQLInterface::instance (int FLAGS) {
	if (p_instance) delete p_instance;
	
	//if (FLAGS & FILEBASE)
	//	p_instance = new class FileBase;
	//else
		p_instance = new class SQLiteBase;
	
	return p_instance;
}

SQLInterface * SQLInterface::instance () {
	if (p_instance) return p_instance;
	return instance (0);
}
