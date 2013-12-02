#include <basetypes.h>
#include <entities.h>

Developer::Developer (const char *name, const char *email, const char *password) {
	this->email.set(email);
	this->name.set(name);
	this->password.set(password);
}
