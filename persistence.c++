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

// STUB SQLITE EMULATOR
///////////////////////

class StubBase: public SQLInterface {
	private:
	public:
		bool Login (Developer *);
		StubBase () {
			
		}
};

bool StubBase::Login (Developer * developer) {
	password password;
	password.set("12345");
	if ((strcmp(developer->email.value, "me@tmergulhao.com") == 0) &&
		developer->password == password)
		return true;
	return false;
}

// SINGLETON STATEMENTS
///////////////////////

SQLInterface * SQLInterface::p_instance = 0;

SQLInterface * SQLInterface::instance (int FLAGS) {
	if (FLAGS & STUBEBASE)
		p_instance = new class StubBase;
	else
		p_instance = new class SQLiteBase;
	return p_instance;
}
