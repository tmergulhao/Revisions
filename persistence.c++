#include "persistence.h"

bool SQLiteBase::Login (* developer) { return true; }

bool StubBase::Login (* developer) {
	if (strcmp(developer->email, "me@tmergulhao.com") == 0 &&
		strcmp(developer->email, "12345") == 0) return true;
	return false;
}
