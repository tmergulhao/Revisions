#ifndef ENTITIES_H
#define ENTITIES_H

// ANSI C Libs
//////////////
//#include <stdbool.h>
//#include <time.h>

// Local Libs
/////////////
#include <basetypes.h>

//-----------------------------------------------------------------------
// ENTITIES
//-----------------------------------------------------------------------

// DEVELOPER
////////////

class Developer {
	public:
		class email email;
		class dev_name name;
		class password password;
		
		Developer () {}
		Developer (const char *, const char *, const char *);
};

// DEFECT
/////////

class Defect {
	public:
		string name;
		string description; // 30 caracteres
		email developer;
		code id_code;
		string votes; // de 0 a 100
		string state;
		string opening;
		string closing;
		code product;
};

// PRODUCT
//////////

class Product {
	public:
		string name;
		code id_code;
		version version;
		email developer;
};

#endif
