#include <string.h>
#include <stdbool.h>

#include <iostream>
using namespace std;

#include "tests.h"
#include "basetypes.h"
#include "command.h"

void CommandWord::Nxt () {
	if (walker == NULL) walker = word;
	else while (*walker != '\0') walker++;
	
	walker++;
	wordcount--;
	
	if (*walker == '\0') walker = NULL;
}

void CommandWord::Set () {
	int charcount = 0;
	
	wordcount = 0;
	walker = word;
	
	while ((*walker = getchar()) != '\n') {
		if (*walker == ' ') {
			*walker = '\0';
			if ((walker > word) && walker[-1] != '\0') {
				walker ++;
				wordcount++;
			}
		} else {
			walker++;
		}
		// ESC ?
	}
	walker[0] = '\0';
	walker[1] = '\0';
	
	if (walker == word) walker = NULL;
	else walker = word;
	
	// if (charcount == 0) throw NO_CHARS;
}

bool CommandWord::operator== (const char * sample) {
	if (walker) {
		if (strcmp(walker,sample) == 0)
			return true;
	}
	
	return false;
}

bool CommandWord::operator!= (const char * sample) {
	return !(*this == sample);
}

bool CommandWord::operator++ (int) {
	if (walker == NULL) walker = word;
	else while (*walker != '\0') walker++;
	
	walker++;
	wordcount--;
	
	if (*walker == '\0') walker = NULL;
	
	return walker;
}

void CLTUI::PrintScope () {
	cout << "| ";
}

void CLTUI::PrintFile (const char * path) {
	FILE *pFile = fopen (path, "r");
	char cache;
	
	if (pFile) while ((cache = getc(pFile)) != EOF) putchar(cache);
	
	// cout <<	"Word:" << setw(15) << hash->key << 
	//			" Count:" << hash->value << endl;
}

void CLTUI::GetFields (int mode) {
	char field[31];
	
	// cin >> name;
	
	if (mode & EMAIL_INPUT) {
		try {
			cout << "EMAIL: ";
			cin.getline(field,31);
			Dev->email.set(field);
		}
		catch (email_error) {
			cout << "INVALID EMAIL" << endl;
			GetFields(EMAIL_INPUT);
		}
	}
	
	if (mode & PASS1_INPUT) {
		try {
			cout << "PASSWORD: ";
			cin.getline(field,31);
			Dev->password.set(field);
		}
		catch (password_error) {
			cout << "INVALID PASSWORD" << endl;
			GetFields(PASS1_INPUT);
		}
	}
	
	if (mode & PASS2_INPUT) {
		try {
			cout << "PASSWORD: ";
			cin.getline(field,31);
			password->set(field);
		}
		catch (password_error) {
			cout << "INVALID PASSWORD" << endl;
			GetFields(PASS2_INPUT);
		}
	}
}

void CLTUI::ParseOpt () {
	// QUIT
	if (((*Word) == "quit") || ((*Word) == "q")) {
		if ((*Word)++) throw SUGEST_MANUAL;
		else throw QUIT_APPLICATION;
	} else
	
	// LOGOUT
	if ((*Word) == "logout") {
		cout << "\tUser logged out." << endl;
	} else
	
	// MANUAL
	if (((*Word) == "?") || ((*Word) == "help")) {
		throw VIEW_MANUAL;
	} else
	
	// TEST
	if (((*Word) == "test") || ((*Word) == "tst")) {
		if (!((*Word)++) || (*Word) == "&&")
			TESTENVIROMENT::instance()->TestTypes->RunTests();
		else throw SUGEST_MANUAL;
	} else
	
	// LOGIN
	if ((*Word) == "login") {
		(*Word)++;
		if (Word->Str() && (*Word) != "&&") throw SUGEST_MANUAL;
		else {
			GetFields(	EMAIL_INPUT |
						PASS1_INPUT);
		}
	} else
	
	// LIST SCOPE
	if (((*Word) == "list") || ((*Word) == "ls")) {
		if (!((*Word)++) || (*Word) == "&&")
			cout << "\tList items on scope." << endl;
		else throw SUGEST_MANUAL;
	} else
	
	// SIGN IN
	if ((*Word) == "sign") {
		(*Word)++;
		
		if ((*Word) == "up") (*Word)++;
		
		if (Word->Str())
			throw SUGEST_MANUAL;
		else {
			cout << "\tEnter the new user info." << endl;
			GetFields(	NAME_INPUT |
						EMAIL_INPUT |
						PASS1_INPUT |
						PASS2_INPUT);
		}
	} else
	
	// CHANGE PASS
	if ((*Word) == "pass" || (*Word) == "password") {
		if (Word->HasNxt())
			throw SUGEST_MANUAL;
		else {
			cout << "\tAbout to change password." << endl;
			GetFields(	PASS1_INPUT |
						PASS2_INPUT);
		}
	} else
	
	// CHAGE NAME
	if ((*Word) == "name") {
		if (Word->HasNxt())
			throw SUGEST_MANUAL;
		else {
			cout << "\tAbout to change name." << endl;
			GetFields(	NAME_INPUT);
		}
	} else
	
	{
		if (Word->Str()) throw SUGEST_MANUAL;
	}
	
	if ((*Word) == "&&") {
		(*Word)++;
		ParseOpt();
	}
	
}

void CLTUI::Run () {
	char * c;
	
	PrintFile("welcome.txt");
	
	while (true) {
		try {
			PrintScope();
			Word->Set();
			ParseOpt();
		}
		catch (AppStates state) {
			if (state == QUIT_APPLICATION) {
				return;
			}
		
			else if (state == VIEW_MANUAL) {
				PrintFile("manual.txt");
			}
		
			else if (state == SUGEST_MANUAL) {
				cout << "\tUse ? to seek help." << endl;
			}
		}
	}
}
