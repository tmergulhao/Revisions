#include <string.h>
#include <stdbool.h>

#include <iostream>
using namespace std;

#include "command.h"

#include "tests.h"
#include "basetypes.h"

class CommandWord {
	public:
		char word[50], *walker;
		int wordcount;
	
		CommandWord () {
			word[0] = word[1] = '\0';
			walker = NULL;
			wordcount = 0;
		}
		
		inline char * Str () { return walker; }
		
		void Set ();
		void Nxt ();
		
		inline int HasNxt () {
			return wordcount;
		}
		
		bool operator== (const char * sample);
		void operator++ ();
};

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

void CommandWord::operator++ () {
	if (walker == NULL) walker = word;
	else while (*walker != '\0') walker++;
	
	walker++;
	wordcount--;
	
	if (*walker == '\0') walker = NULL;
}

CLTUI::CLTUI () {
	Word = new class CommandWord;
}

CLTUI::~CLTUI () {
	delete Word;
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

void CLTUI::ParseOpt () {
	
	if (*Word == "&&") Word->Nxt();
	
	// QUIT
	if ((*Word == "quit") || (*Word == "q")) {
		Word->Nxt();
		if (Word->Str()) {
			throw SUGEST_MANUAL;
		}
		else
			throw QUIT_APPLICATION;
	} else
	
	// MANUAL
	if ((*Word == "?") || (*Word == "help")) {
		Word->Nxt();
		if (Word->Str()) {
			throw SUGEST_MANUAL;
		}
		throw VIEW_MANUAL;
	} else
	
	// TEST
	if ((*Word == "test") || (*Word == "tst")) {
		Word->Nxt();
		if (*Word == "&&") {
			TESTENVIROMENT::instance()->TestTypes->RunTests();
		} else throw SUGEST_MANUAL;
	} else
	
	// LOGIN
	if (*Word == "login") {
		Word->Nxt();
		if (Word->Str()) {
			if (*Word == "out")
				cout << "\tUser logged out." << endl;
			else throw SUGEST_MANUAL;
		}
		else {
			cout << "\tEnter user data." << endl << 
				"\t\tMail:" << endl << 
				"\t\tPass:" << endl;
			// interface de ENUM para dados a serem captados
			//try {
			//	GetFields(LOGIN);
			//	MAIL_INPUT & PASS_INPUT
			//	101000 = 100000 | 001000
			//}
			//catch (esc)
		}
	} else
	
	// SIGN IN
	if (*Word == "sign") {
		Word->Nxt();
		
		if (*Word == "up") Word->Nxt();
		
		if (Word->Str())
			throw SUGEST_MANUAL;
		else {
			cout << "\tEnter user data." << endl << 
				"\t\tName:" << endl << 
				"\t\tMail:" << endl << 
				"\t\tPass:" << endl;
			// interface de ENUM para dados a serem captados
			//try {
			//	GetFields(SIGNUP);
			//	NAME_INPUT & MAIL_INPUT & PASS_INPUT
			//	111000 = 100000 | 010000 | 001000
			//}
			//catch (esc)
		}
	} else
	
	// CHANGE PASS
	if (*Word == "pass" || *Word == "password") {
		if (Word->HasNxt())
			throw SUGEST_MANUAL;
		else {
			cout << "\tAbout to change password." << endl;
			// interface de ENUM para dados a serem captados
			//try {
			//	GetFields(CHANGE_PASS);
			//	PASS_INPUT & NAME_INPUT
			//	001100 = 001000 | 000100
			//}
			//catch (esc)
		}
	} else
	
	// CHAGE NAME
	if (*Word == "name") {
		if (Word->HasNxt())
			throw SUGEST_MANUAL;
		else {
			cout << "\tAbout to change name." << endl;
			// interface de ENUM para dados a serem captados
			//try {
			//	GetFields(CHANGE_PASS);
			//	PASS_INPUT & PASS_INPUT2
			//	011000 = 010000 | 001000
			//}
			//catch (esc)
		}
	} else
	
	// LIST SCOPE
	if (*Word == "list" || *Word == "ls") {
		Word->Nxt();
		if (!(*Word == "&&"))
			throw SUGEST_MANUAL;
		else {
			cout << "\tList items on scope." << endl;
			// LIST ITEMS OF SCOPE
		}
	} else
	
	// FETCH PRODUCT
	if (*Word == "product" || *Word == "prod") {
		Word->Nxt();
		if (Word->Str()) {
			cout << "\tSelect product on scope." << endl;
			// VALIDATE ID
			// SWITCH TO PRODUCT
			// SHOW INFO
		}
		else
			throw SUGEST_MANUAL;
	} else
	
	// FETCH ISSUE
	if (*Word == "issue" || *Word == "issue") {
		Word->Nxt();
		if (Word->Str()) {
			cout << "\tSelect issue on scope." << endl;
			// VALIDATE ID
			// VALIDATE OPTION
			// OR SHOW INFO
		}
		else
			throw SUGEST_MANUAL;
	} else
	
	{
		if (Word->Str()) throw SUGEST_MANUAL;
	}
	
	if (*Word == "&&") {
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

/*
int main (int argc, char **argv) {
	char * field1 = new char [1000];
	char * field2 = new char [1000];
	password * password1, * password2;
	
	sqlite3 *base;

	// cin >> name;
	
	cout << "Hello World!";

	try {
		cin.getline(field1,1000);
	
		password1 = new password;
		password1->set(field1);
	}
	catch (password_error error) {
		if (error == INVALID_SIZE) {
			cout << "INVALID SIZE\n";
		}
		if (error == EQUAL_CHARS) {
			cout << "INVALID EQUAL\n";
		}
	}
	
	delete [] field1;
	
	try {
		cin.getline(field2,1000);
	
		password2 = new password;
		password2->set(field2);
	}
	catch (password_error error) {
		if (error == INVALID_SIZE) {
			cout << "INVALID SIZE\n";
		}
		if (error == EQUAL_CHARS) {
			cout << "INVALID EQUAL\n";
		}
	}
	
	delete [] field2;
	
	try {
		((*password1) == (*password2));
	}
	catch (password_matching status) {
		if (status == EQUAL) cout << "EQUAL\n";
		else cout << "NOT_EQUAL\n";
	}

	delete password1;
	delete password2;

	return 0;
}
*/
