// C++ Libs
///////////
#include <iostream>
using namespace std;

// ANSI C Libs
//////////////
#include <string.h>
#include <stdbool.h>

// Local Libs
/////////////
#include <main.h>
#include <entities.h>
#include <tests.h>
#include <controller.h>
#include <command.h>

#define	ctab	"\t"

// WEB SERVER USER INTERFACE
////////////////////////////

class WEBUI: public MethaUI {
		class Developer * Dev;
		class password * password;
	public:
		WEBUI (int FLAGS) {
			CONTROLLER::instance(FLAGS);
			
			Dev = new class Developer;
			password = new class password;
		}
		
		void Run() {}
		
		~WEBUI () {
			delete Dev;
			delete password;
			
			delete CONTROLLER::instance();
		}
};

// COMMAND WORD
///////////////

#define WORDNUMBER	30
#define WORDLENGTH	30

class CommandWord {
	public:
		char *word[WORDNUMBER], *walker;
	
		CommandWord (const char * input) {
			Allocate();
			Set(input);
		}
		CommandWord () {
			Allocate();
		}
		~CommandWord () {
			for (int i = 0; i < WORDNUMBER; i++) {
				delete word[i];
			}
		}
		
		inline void Allocate () {
			for (int i = 0; i < WORDNUMBER; i++) {
				word[i] = new char [WORDLENGTH];
			}
			*(word[0]) = '\0';
		}
		
		inline char * Str () {
			return walker;
		}
		inline bool Null () {
			if (walker == NULL || (*this) == "&&") return true;
			return false;
		}
		inline void Kill () {
			walker = NULL;
		}
		
		void Set ();
		void Set (const char *);
		
		bool operator== (const char * sample);
		bool operator!= (const char * sample);
		bool operator++ (int);
};

void CommandWord::Set () {
	int wordcount = 0;
	walker = *word;
	
	while ((*walker = getchar()) != '\n') {
		if (*walker == ' ') {
			if (walker == word[wordcount]) {}
			else {
				*walker = '\0';
				wordcount++;
				walker = word[wordcount];
			}
		} else {
			walker++;
		}
	}
	*walker = '\0';
	
	for (wordcount = wordcount+1; wordcount < WORDNUMBER; wordcount++) {
		*(word[wordcount]) = '\0';
	}
	
	if (walker == *word) walker = NULL;
	else walker = word[0];
}

void CommandWord::Set (const char * queue) {
	int wordcount = 0;
	walker = *word;
	
	int size = strlen(queue);
	
	while ((*walker = *queue) != '\n' && size) {
		if (*walker == ' ') {
			if (walker == word[wordcount]) {}
			else {
				*walker = '\0';
				wordcount++;
				walker = word[wordcount];
			}
		} else {
			walker++;
		}
		queue++;
		size--;
	}
	*walker = '\0';
	
	for (wordcount = wordcount+1; wordcount < WORDNUMBER; wordcount++) {
		*(word[wordcount]) = '\0';
	}
	
	if (walker == *word) walker = NULL;
	else walker = word[0];
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
	if (walker == NULL) return false;
	
	int i;
	
	for (i = 0; walker != word[i]; i++) {
		if (*(word[i]) == '\0') return walker = NULL;
	}
	
	if (i == WORDNUMBER-1) {
		return walker = NULL;
	}
	
	walker = word[i+1];
	
	if (*walker == '\0') return walker = NULL;
	
	return true;
}

// COMMAND LINE USER INTERFACE
//////////////////////////////

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
			
			CONTROLLER::instance(FLAGS);
			
			Dev = new class Developer;
			password = new class password;
			
			if (FLAGS & TSTMODE) 
				Word = new class CommandWord ("tst && q");
			else
				Word = new class CommandWord;
		}
		
		void Run();
		
		void PrintScope ();
		void ParseOpt ();
		
		void ParseUsr ();
		void ParseHelp ();
		
		inline void SuggestManual () {
			cout << ctab << "Use ? to seek help." << endl;
			Word->Kill();
		}
		
		void PrintFile (const char *);
		
		void GetFields (int);
		
		~CLTUI () {
			delete Word;
			delete Dev;
			delete password;
			
			delete CONTROLLER::instance();
			delete TESTENVIROMENT::instance();
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
		catch (invalid_argument error) {
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
		catch (invalid_argument error) {
			cout << ctab << "INVALID PASSWORD" << endl;
			GetFields(PASS1_INPUT);
		}
	}
	
	if (mode & PASS2_INPUT) {
		try {
			cout << "PASSWORD: ";
			cin.getline(field,31);
			password->set(field);
			
			if (Dev->password.value.compare(password->value)) {
				cout << ctab << "PASSWORDS NOT MATCHIN" << endl;
				GetFields(PASS2_INPUT);
			}
		}
		catch (invalid_argument error) {
			cout << ctab << "INVALID PASSWORD" << endl;
			GetFields(PASS2_INPUT);
		}
	}
}

void CLTUI::ParseHelp() {
	(*Word)++;
	
	if (Word->Null()) {
		PrintFile("manual.txt");
		Word->Kill();
	}
	else 
	
	if (*Word == "new") {
		cout << ctab << "HELP NEW" << endl;
	}
	else SuggestManual();
	
	Word->Kill();
}

void CLTUI::ParseUsr () {
	(*Word)++;
	if (Word->Null()) {
		cout << ctab << "LOGGED OUT" << endl;
	} else 
	if (*Word == "new") {
		(*Word)++;
		if (!(Word->Null())) {
			try {
				Dev->email.set(Word->Str());
				GetFields(	NAME_INPUT |
							PASS1_INPUT |
							PASS2_INPUT);
				cout << ctab << "USER ADDED" << endl;
				(*Word)++;
			}
			catch (invalid_argument error) {
				cout << ctab << "INVALID EMAIL" << endl;
			}
		}
		else SuggestManual();
	} else 
	
	if (*Word == "rm") {
		(*Word)++;
		if (!(Word->Null())) {
			try {
				Dev->email.set(Word->Str());
				cout << ctab << "USER REMOVED" << endl;
				(*Word)++;
			}
			catch (invalid_argument error) {
				cout << ctab << "INVALID EMAIL" << endl;
			}
		}
		else SuggestManual();
	} else 
	
	{
		try {
			Dev->email.set(Word->Str());
			GetFields(	PASS1_INPUT);
			
			if (CONTROLLER::instance()->Login(Dev)) {
				cout << ctab << "LOGGED IN" << endl;
			}
			else
				cout << ctab << "WRONG INPUT" << endl;
			
			(*Word)++;
		}
		catch (invalid_argument error) {
			cout << ctab << "INVALID EMAIL" << endl;
		}
	}
}

void CLTUI::ParseOpt () {
	if ((*Word == "quit") || 
		(*Word == "q")) {
		(*Word)++;
		if (Word->Str()) {
			SuggestManual();
		}
		else throw QUIT_APP;
	} else
	
	if ((*Word == "?") || 
		(*Word == "help") || 
		(*Word == "man") || 
		(*Word == "manual")) ParseHelp();
	else
	
	if ((*Word == "test") || 
		(*Word == "tst")) {
		(*Word)++;
		if (Word->Null())
			TESTENVIROMENT::instance()->RunTests();
		else SuggestManual();
	} else
	
	if ((*Word == "list") || 
		(*Word == "ls")) {
		(*Word)++;
		if (Word->Null())
			cout << ctab << "List items on scope." << endl;
		else SuggestManual();
	} else
	
	// USER ACTIONS
	if ((*Word == "usr") || 
		(*Word == "user")) ParseUsr();
	
	else
	
	{
		if (Word->Str()) SuggestManual();
	}
	
	if (Word->Null()) (*Word)++;
}

void CLTUI::Run () {
	while (true) {
		if (Word->Str())
			ParseOpt();
		else {
			PrintScope();
			Word->Set();
		}
	}
}

// SINGLETON STATEMENTS
///////////////////////

MethaUI * MethaUI::p_instance = 0;

MethaUI * MethaUI::instance (int FLAGS) {
	if (p_instance) delete p_instance;
	
	if (FLAGS & CLTMODE)
		p_instance = new class CLTUI (FLAGS);
	else
		p_instance = new class CLTUI (FLAGS);
		//p_instance = new class WEBUI (FLAGS);
		//p_instance = new class OSXUI (FLAGS);
	
	return p_instance;
}

MethaUI * MethaUI::instance () {
	if (p_instance) return p_instance;
	return instance (0);
}
