// ANSI C Libs
//////////////
#include <string.h>

// Local Libs
/////////////
#include <basetypes.h>

#define ALPHA(X)		(BETWEEN('a',X,'z')||BETWEEN('A',X,'Z'))
#define ALPHANUM(X)		(ALPHA(X)||BETWEEN('0',X,'9'))

//-----------------------------------------------------------------------
// DEVELOPER NAMES
//-----------------------------------------------------------------------

/*!
Receaves dinamically allocated string, purges the previous value and assigns the new one.
Evaluates if valid and throw exceptions for errors.
@param[in]	input	Dinamically allocated string
*/
void dev_name::set (char * input) throw (invalid_argument) {
	int name_size = 0, pull = 0;
	
	if (input[0] == ' ') {
		pull++;
		input[0] = input[1];
	}
	while (*input != '\0') {
		if (ALPHA(input[0]) || input[0] == ' ') {}
		else throw invalid_argument("NUMBERS");
		
		if (input[0] == ' ' && input[pull+1] == ' ') pull++;
		
		name_size++;
		input++;
		
		if (pull) input[0] = input[pull];
	}
	if (name_size == 0) throw invalid_argument("NULL NAME");
	
	if (strlen(input) > 15) throw invalid_argument("SIZE OVERFLOW");
	
	string queue_str(input);
	
	value =  queue_str;
}
void dev_name::set (const char * input) throw (invalid_argument) {
	char * queue = new char [strlen(input) + 1];
	strcpy(queue, input);
	set(queue);
	
	delete [] queue;
}

//-----------------------------------------------------------------------
// EMAIL
//-----------------------------------------------------------------------

/*!
Receaves dinamically allocated string, purges the previous value and assigns the new one.
Evaluates if valid and throw exceptions for errors.
@param[in]	input	Dinamically allocated string
*/
void email::set (char * input) throw (invalid_argument) {
	bool separation = false, queue = false;
	
	char * mark = input;
	
	if (ALPHANUM(mark[0])) {}
	else throw invalid_argument("STARTS WITH NON ALPHANUMBER");
	
	while (*mark != '\0') {
		if (ALPHANUM(mark[0]) || mark[0] == '.' || mark[0] == '_' || mark[0] == '@') {}
		else throw invalid_argument("INVALID CHAR");
		
		if (mark[0] == '@') {
			if (separation) throw invalid_argument("TWO AT SIGNS");
			separation = true;
			queue = true;
		} else if (mark[0] == '_' && separation) {
			throw invalid_argument("NON ALPHA ON DOMAIN PATH");
		} else if (mark[0] == '.') {
			if (queue && separation) throw invalid_argument("NO TOP DOMAIN");
			queue = true;
		} else queue = false;
		
		mark++;
	}
	if (!separation || queue) throw invalid_argument("NO DOMAIN");
	
	string queue_str(input);
	
	value =  queue_str;
}
void email::set (const char * input) throw (invalid_argument) {
	char * queue = new char [strlen(input) + 1];
	strcpy(queue, input);
	set(queue);
	
	delete [] queue;
}

//-----------------------------------------------------------------------
// PASSWORDS
//-----------------------------------------------------------------------

/*!
Receaves dinamically allocated string, purges the previous value and assigns the new one.
Evaluates if valid and throw exceptions for errors.
@param[in]	input	Dinamically allocated string
*/
void password::set (char * input) throw (invalid_argument) {
	if (strlen(input) != 5) throw invalid_argument("INVALID SIZE");
	
	for (int i = 0; i < 5; i++) {
		if (!ALPHANUM(input[i])) throw invalid_argument("NON ALPHANUMBER");
		for (int j = i+1; j < 5; j++) {
			if (input[i] == input[j]) throw invalid_argument("EQUAL CHARS");
		}
	}
	
	string queue_str(input);
	
	value =  queue_str;
}
void password::set (const char * input) throw (invalid_argument) {
	if (strlen(input) != 5) throw invalid_argument("INVALID SIZE");
	
	char * queue = new char [6];
	strcpy(queue, input);
	
	set(queue);
	
	delete [] queue;
}
