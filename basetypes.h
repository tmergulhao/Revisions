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

class basetype {
	public:
		char * value;
		
		/*!
		*	\brief Recebe e valida valor.
		*	Recebe ponteiro para constante ou caracter.
		*	Avalia validez da entrada e lança exceção apropriada.
		*	@param[in]	input	Ponteiro de vetor de caracteres.
		*/
		virtual void set (char * input) = 0;
		virtual void set (const char * input) = 0;
};

/**
*	\brief Classe com alocação e avaliação de valores para nome de desenvolvedor.
*	Avalia o nome quanto ao comprimento padrão, 15 dígitos que sejam:
*	* letras do alfabeto sem acentuação maiúsculas ou minúsculas;
*	* espaços.
*/
class dev_name : public basetype {
	public:
		dev_name () {
			value = new char [16];
		}
		~dev_name () {
			delete [] value;
		}
		
		void set (char *);
		void set (const char *);
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
class email : public basetype {
	public:
		/**
		* \brief The pointer to the dinamically allocated character string
		*/
		email () {
			value = new char [60];
		}
		~email () {
			delete [] value;
		}
		
		void set (char *);
		void set (const char *);
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
* \brief Class used to store, match and validate developer passwords.
*/
class password : public basetype {
		/**
		* \brief O array de valores caracter com largura 5 mais 1 de finalização
		*/
		//char value [6];
	public:
		password () {
 			// 5 digits
 			value = new char [6];
 		}
 		~password () {
 			delete [] value;
 		}
		
		void set (char *);
		void set (const char *);
};

// IDENTIFIER

class identifier {
		char * value;
	public:
		identifier () {
			// 4 digits
			value = new char [5];
			// generares value
		}
		identifier (char * input) {
			// 4 digits
			value = new char [5];
			// validates value
		}
		~identifier () {
			delete value;
		}
		int get() {return 0001;}
};

// VERSION

class version {
		char * value;
	public:
		//version () {
		//	for (int i = 0; i < 4; i++) value[i] = '0';
		//		value[4] = '\0';
		//}
		version () {
			// 4 digits
			value = new char [5];
			// generares value
		}
		~version () {
			delete value;
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