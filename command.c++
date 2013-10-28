#include <string.h>
#include <stdbool.h>

#include <iostream>
using namespace std;

#include "tests.h"
#include "basetypes.h"
#include "command.h"
#include "main.h"

#define	ctab	"\t"

// COMMAND WORD
///////////////

class CommandWord {
	public:
		char word[1000], *walker;
		int wordcount;
	
		CommandWord () {
			word[0] = word[1] = '\0';
			walker = NULL;
			wordcount = 0;
		}
		
		inline char * Str () { return walker; }
		
		void Set ();
		
		bool operator== (const char * sample);
		bool operator!= (const char * sample);
		bool operator++ (int);
};

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
	}
	walker[0] = '\0';
	walker[1] = '\0';
	
	if (walker == word) walker = NULL;
	else walker = word;
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

// COMMAND LINE USER INTERFACE
//////////////////////////////

typedef enum {
	QUIT_APPLICATION = 0,
	VIEW_MANUAL,
	SUGEST_MANUAL
} UI_STATES;

typedef enum {
	NAME_INPUT		= (0x1 << 0),
	PASS1_INPUT		= (0x1 << 1),
	PASS2_INPUT		= (0x1 << 2),
	ID_INPUT		= (0x1 << 3),
	STATE_INPUT		= (0x1 << 4)
} INPUT_MODES;

class CLTUI: public MethaUI {
		class CommandWord * Word;
		class Developer * Dev;
		class password * password;
	public:
		CLTUI (int FLAGS) {
			PrintFile("welcome.txt");
			
			SQLInterface::instance(FLAGS);
	
			Word = new class CommandWord;
			Dev = new class Developer;
			password = new class password;
		}
		
		void Run();
		void ParseOpt ();
			void ParseUsr ();
		void PrintScope ();
		void PrintFile (const char *);
		
		void GetFields (int);
		
		~CLTUI () {
			delete Word;
			delete Dev;
			delete password;
		}
};

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
	
	if (mode & NAME_INPUT) {
		try {
			cout << "NAME: ";
			cin.getline(field,31);
			Dev->name.set(field);
		}
		catch (dev_name_error) {
			cout << ctab << "INVALID NAME" << endl;
			GetFields(NAME_INPUT);
		}
	}
	
	if (mode & PASS1_INPUT) {
		try {
			cout << "PASSWORD: ";
			cin.getline(field,31);
			Dev->password.set(field);
		}
		catch (password_error) {
			cout << ctab << "INVALID PASSWORD" << endl;
			GetFields(PASS1_INPUT);
		}
	}
	
	if (mode & PASS2_INPUT) {
		try {
			cout << "PASSWORD: ";
			cin.getline(field,31);
			password->set(field);
			
			if (!(Dev->password == *password)) {
				cout << ctab << "PASSWORDS NOT MATCHIN" << endl;
				GetFields(PASS2_INPUT);
			}
		}
		catch (password_error) {
			cout << ctab << "INVALID PASSWORD" << endl;
			GetFields(PASS2_INPUT);
		}
	}
}

void CLTUI::ParseUsr () {
	if (!((*Word)++) || (*Word) == "&&") {
		cout << ctab << "LOGGED OUT" << endl;
	} else 
	if ((*Word) == "new") {
		if ((*Word)++) {
			try {
				Dev->email.set(Word->Str());
				GetFields(	NAME_INPUT |
							PASS1_INPUT |
							PASS2_INPUT);
				cout << ctab << "USER ADDED" << endl;
				(*Word)++;
			}
			catch (email_error) {
				cout << ctab << "INVALID EMAIL" << endl;
			}
		}
		else throw SUGEST_MANUAL;
	} else 
	
	if ((*Word) == "rm") {
		if ((*Word)++) {
			try {
				Dev->email.set(Word->Str());
				cout << ctab << "USER REMOVED" << endl;
				(*Word)++;
			}
			catch (email_error) {
				cout << ctab << "INVALID EMAIL" << endl;
			}
		}
		else throw SUGEST_MANUAL;
	} else 
	
	{
		try {
			Dev->email.set(Word->Str());
			GetFields(	PASS1_INPUT);
			
			if (SQLInterface::instance()->Login(Dev)) {
				cout << ctab << "LOGGED IN" << endl;
			}
			else
				cout << ctab << "WRONG INPUT" << endl;
			
			(*Word)++;
		}
		catch (email_error) {
			cout << ctab << "INVALID EMAIL" << endl;
		}
	}
}

void CLTUI::ParseOpt () {
	if (((*Word) == "quit") || ((*Word) == "q")) {
		if ((*Word)++) throw SUGEST_MANUAL;
		else throw QUIT_APPLICATION;
	} else
	
	if (((*Word) == "?") || ((*Word) == "help")) {
		throw VIEW_MANUAL;
		(*Word)++;
	} else
	
	if (((*Word) == "test") || ((*Word) == "tst")) {
		if (!((*Word)++) || (*Word) == "&&")
			TESTENVIROMENT::instance()->TestTypes->RunTests();
		else throw SUGEST_MANUAL;
	} else
	
	if (((*Word) == "list") || ((*Word) == "ls")) {
		if (!((*Word)++) || (*Word) == "&&")
			cout << ctab << "List items on scope." << endl;
		else throw SUGEST_MANUAL;
	} else
	
	// USER ACTIONS
	if (((*Word) == "usr") || ((*Word) == "user")) ParseUsr();
	
	else
	
	{
		if (Word->Str()) throw SUGEST_MANUAL;
	}
	
	if ((*Word) == "&&") {
		(*Word)++;
		ParseOpt();
	}
}

void CLTUI::Run () {
	while (true) {
		try {
			PrintScope();
			Word->Set();
			ParseOpt();
		}
		catch (UI_STATES state) {
			if (state == QUIT_APPLICATION)
				return;
		
			else if (state == VIEW_MANUAL)
				PrintFile("manual.txt");
		
			else if (state == SUGEST_MANUAL)
				cout << ctab << "Use ? to seek help." << endl;
		}
	}
}

// SINGLETON STATEMENTS
///////////////////////

MethaUI * MethaUI::p_instance = 0;

MethaUI * MethaUI::instance (int FLAGS) {
	if (FLAGS & CLTMODE)
		p_instance = new class CLTUI (FLAGS);
	return p_instance;
}
