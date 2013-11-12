#include <string.h>

#include "basetypes.h"

//-----------------------------------------------------------------------
// DEVELOPER NAMES
//-----------------------------------------------------------------------

/*!
Receaves dinamically allocated string, purges the previous value and assigns the new one.
Evaluates if valid and throw exceptions for errors.
@param[in]	input	Dinamically allocated string
*/
void dev_name::set (char * input) {
	int name_size = 0, pull = 0;
	
	if (input[0] == ' ') {
		pull++;
		input[0] = input[1];
	}
	while (*input != '\0') {
		if (BETWEEN('a',input[0],'z') || BETWEEN('A',input[0],'Z') || input[0] == ' ') {}
		else throw NUMBERS;
		
		if (input[0] == ' ' && input[pull+1] == ' ') pull++;
		
		name_size++;
		input++;
		
		if (pull) input[0] = input[pull];
	}
	if (name_size == 0) throw NULL_NAME;
	
	if (strlen(input) > 15) throw TOO_BIG;
	
	strcpy(value, input);
}
void dev_name::set (const char * input) {
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
void email::set (char * input) {
	bool separation = false, queue = false;
	
	char * mark = input;
	
	if (BETWEEN('a',mark[0],'z')) {}
	else throw STD_INVALID;
	
	while (*mark != '\0') {
		if (BETWEEN('a',mark[0],'z') || mark[0] == '.' || mark[0] == '_' || mark[0] == '@') {}
		else throw STD_INVALID;
		
		if (mark[0] == '@') {
			if (separation) throw STD_INVALID;
			separation = true;
			queue = true;
		} else if (mark[0] == '_' && separation) {
			throw STD_INVALID;
		} else if (mark[0] == '.') {
			if (queue && separation) throw STD_INVALID;
			queue = true;
		} else queue = false;
		
		mark++;
	}
	if (!separation || queue) throw STD_INVALID;
	
	strcpy(value, input);
}
void email::set (const char * input) {
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
void password::set (char * input) {
	if (strlen(input) != 5) throw INVALID_SIZE;
	
	for (int i = 0; i < 5; i++)
		for (int j = i+1; j < 5; j++)
			if (input[i] == input[j])
				throw EQUAL_CHARS;
	
	strcpy(value, input);
}
void password::set (const char * input) {
	if (strlen(input) != 5) throw INVALID_SIZE;
	
	char * queue = new char [6];
	strcpy(queue, input);
	
	set(queue);
	
	delete [] queue;
}
