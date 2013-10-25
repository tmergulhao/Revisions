#ifndef BASICTYPES_H
#define BASICTYPES_H

#include <stdbool.h>
#include <time.h>

#define	BETWEEN(X,Y,Z)		(Y >= X && Y <= Z)

//-----------------------------------------------------------------------
// BASIC TYPES
//-----------------------------------------------------------------------

// DEVELOPER NAME

/**
* Errors in developer naming
*/
typedef enum {
	NUMBERS,	/**< Using numbers */
	NULL_NAME,	/**< Empty string */
	TOO_BIG		/**< Bigger than 30 digits */
} dev_name_error;
/**
* \brief Class used to store and validate developer names.
*/
class dev_name {
	public:
		/**
		* \brief The pointer to the dinamically allocated character string
		*/
		char value [16];
		/*!
		Receaves dinamically allocated string, purges the previous value and assigns the new one.
		Evaluates if valid and throw exceptions for errors.
		@param[in]	input	Dinamically allocated string
		*/
		void set (char *);
};

// EMAIL

/**
* Errors in email validation
*/
typedef enum {
	STD_INVALID	/**< Invalid password */
} email_error;
/**
* \brief Class used to store and validate developer emails.
*/
class email {
	public:
		/**
		* \brief The pointer to the dinamically allocated character string
		*/
		char value[60];
		/*!
		Receaves dinamically allocated string, purges the previous value and assigns the new one.
		Evaluates if valid and throw exceptions for errors.
		@param[in]	input	Dinamically allocated string
		*/
		void set (char *);
};

// PASSWORD

/**
* Errors in password validation
*/
typedef enum {
	INVALID_SIZE,	/**< Different than 5 digits */
	EQUAL_CHARS		/**< Has matching characters */
} password_error;
/**
* Password matching states
*/
typedef enum {
	NOT_EQUAL = 0, EQUAL = 1
} password_matching;
/**
* \brief Class used to store, match and validate developer passwords.
*/
class password {
		/**
		* \brief O array de valores caracter com largura 5 mais 1 de finalização
		*/
		char value[6];
	public:
		/*!
		Receaves dinamically allocated string, purges the previous value and assigns the new one.
		Evaluates if valid and throw exceptions for errors.
		@param[in]	input	Dinamically allocated string
		*/
		void set (char *);
		/*!
		Receaves another password type and matches their values in a private enviroment.
		Throws exceptions for values matching or not.
		@param[in]	comparee	The other password for the operator
		*/
		void operator== (password);
};

// IDENTIFIER

class identifier {
		int value;  // 4 digits
	public:
		identifier () {
			// GENERATE VALUE
		}
		int get() {return 0001;}
};

// VERSION

class version {
		char value[5];
	public:
		version () {
			for (int i = 0; i < 4; i++) value[i] = '0';
				value[4] = '\0';
		}
		void set (char *) {}
		void get() {}
};

//-----------------------------------------------------------------------
// DEVELOPER
//-----------------------------------------------------------------------

class Developer {
		// STACK OF PROJECTS METHATYPE
	public:
		email email;
		dev_name name;
		password password;
		identifier identifier;
};

//-----------------------------------------------------------------------
// BASE
//-----------------------------------------------------------------------

// ABSTRACT PROJECT CLASS

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
		identifier* dev_identifier;
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
		identifier* identifier;
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

#endif