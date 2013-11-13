// C++ Libs
///////////
#include <string>

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
		string GetPassword (string);
		StubBase () {}
		~StubBase () {}
};

string StubBase::GetPassword (string email) {
	string password = "12345";
	return password;
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
