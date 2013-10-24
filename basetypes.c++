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
	
	if (BETWEEN('a',input[0],'z')) {}
	else throw STD_INVALID;
	
	while (*input != '\0') {
		if (BETWEEN('a',input[0],'z') || input[0] == '.' || input[0] == '_' || input[0] == '@') {}
		else throw STD_INVALID;
		
		if (input[0] == '@') {
			if (separation) throw STD_INVALID;
			separation = true;
			queue = true;
		} else if (input[0] == '_' && separation) {
			throw STD_INVALID;
		} else if (input[0] == '.') {
			if (queue && separation) throw STD_INVALID;
			queue = true;
		} else queue = false;
		
		input++;
	}
	if (!separation || queue) throw STD_INVALID;
	
	strcpy(value, input);
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
	int name_size = 0, pull = 0;
	
	if (strlen(input) != 5) throw INVALID_SIZE;
	
	for (int i = 0; i < 5; i++)
		for (int j = i+1; j < 5; j++)
			if (input[i] == input[j]) {
				throw EQUAL_CHARS;
				return;
			}
	
	strcpy(value, input);
}
/*!
Receaves another password type and matches their values in a private enviroment.
Throws exceptions for values matching or not.
@param[in]	comparee	The other password for the operator
*/
void password::operator== (password comparee) {
	for (int i = 0; i < 5; i++) if (value[i] != comparee.value[i]) {
		throw NOT_EQUAL;
		return;
	}
	throw EQUAL;
	return;
}
