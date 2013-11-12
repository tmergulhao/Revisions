#ifndef ENTITIES_H
#define ENTITIES_H

#include <stdbool.h>
#include <time.h>

#include <basetypes.h>

//-----------------------------------------------------------------------
// ENTITIES
//-----------------------------------------------------------------------

// DEVELOPER
////////////

class Developer {
		// STACK OF PROJECTS METHATYPE
	public:
		class email email;
		class dev_name name;
		class password password;
};

/*

// PROJECT
//////////

typedef enum {
	UNCONFIRMED = 0,
	CONFIRMED,
	REPAIRING, // only for issues
	DONE
} methaproject_states;

class methaproject {
	protected:
		char name[16];
		struct tm opening;
		struct tm cloding;
		class developer* developer;
		methaproject_states state;

		//char * getname () {}
		//char * getid () {}
		//struct tm getopening () {}
		//struct tm getclosing () {}
		//char * getdescription () {}
		//char * getdev () {}
		// ...
};

// DEFECT

class defect: public methaproject {
		int votes; // de 0 a 100
		char description[31];
		class identifier* identifier;
};

// PRODUCT

class product: public methaproject {
		// STACK OF DEFECTS
		char version[]; // XX.YY
};

// PROJECT OR DATABASE

class project: public methaproject {
		// STACK OF PRODUCTS
		// STACK OF DEVELOPERS
		// DATABASE CONNECTIONS AND INTERFACES
	public:
		//product () {}		// call for database stablishment
		// ~product () {}	// dumps data on to database
};
*/

#endif
