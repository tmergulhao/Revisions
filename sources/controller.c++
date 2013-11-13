// C++ Libs
///////////
#include <string>
#include <stdexcept>
using namespace std;

// ANSI C Libs
//////////////
#include <string.h>

// Local Libs
#include <main.h>
#include <entities.h>
#include <persistence.h>
#include <controller.h>

// CONTROLLER
/////////////
class StubController: public Controller {
	private:
	public:
		bool Login (Developer *) throw (invalid_argument);
		StubController () {}
};

bool StubController::Login (Developer * developer) throw (invalid_argument) {
	string password = SQLINTERFACE::instance()->GetPassword(developer->email.value);
	
	if (password == "NULL") {
		throw invalid_argument("SQL RETURNED NULL FIELD");
	}
	
	if (developer->password.get().compare(password) == 0) return true;
	return false;
}

// SINGLETON STATEMENTS
///////////////////////

Controller * Controller::p_instance = 0;

Controller * Controller::instance (int FLAGS) {
	if (!p_instance) p_instance = new class StubController;
	return p_instance;
}

Controller * Controller::instance () {
	if (p_instance) return p_instance;
	return instance (0);
}
