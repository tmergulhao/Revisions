#include <string.h>

#include <controller.h>
#include <main.h>

// STUB SQLITE EMULATOR
///////////////////////

class StubController: public Controller {
	private:
	public:
		bool Login (Developer *);
		StubController () {}
};

bool StubController::Login (Developer * developer) {
	password password;
	password.set("12345");
	if ((strcmp(developer->email.value, "me@tmergulhao.com") == 0) &&
		(strcmp(developer->password.value, password.value) == 0))
		return true;
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
