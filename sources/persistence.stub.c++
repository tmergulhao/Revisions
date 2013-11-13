// ANSI C Libs
//////////////
#include <string.h>

// External Libs
////////////////
#include <sqlite3.h>

// Local Libs
/////////////
#include <main.h>
#include <entities.h>
#include <persistence.h>

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
	if (!p_instance) p_instance = new class StubBase;
	return p_instance;
}

SQLInterface * SQLInterface::instance () {
	if (p_instance) return p_instance;
	return instance (0);
}
