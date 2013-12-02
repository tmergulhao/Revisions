// C++ Libs
///////////
#include <stdexcept>
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
		inline bool Nxt () {
			return ((*this)++);
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
		if (strcmp(walker,sample) == 0) {
			(*this)++;
			return true;
		}
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
	
	return walker;
}

// COMMAND LINE USER INTERFACE
//////////////////////////////

class CLTUI: public MethaUI {
		class CommandWord Word;
		class Developer Dev;
		class password Pass;
		class Product Prod;
		class Defect Defct;
	public:
		CLTUI (int FLAGS) {
			//TODO	MODIFY TO PRINT FULL SCOPE
			PrintFile("welcome.txt");
			
			CONTROLLER::instance(FLAGS);
			
			if (FLAGS & TSTMODE) 
				Word.Set("tst && q");
		}
		
		void Run();
		
		void Parse ();
		void Parse_Developer();
		void Parse_Project();
		void Parse_Product();
		void Parse_Defect();
		
		inline void SuggestManual () {
			cout << ctab << "Use ? to seek help.";
			Word.Kill();
		}
		
		void PrintFile (const char *);
		
		void GetDevFields (int);
		void GetProdFields (int);
		void GetDefcFields (int);
		
		~CLTUI () {
			delete CONTROLLER::instance();
			delete TESTENVIROMENT::instance();
		}
};

void CLTUI::PrintFile (const char * path) {
	FILE *pFile = fopen (path, "r");
	char cache;
	
	if (pFile) while ((cache = getc(pFile)) != EOF) putchar(cache);
	
	// cout <<	"Word:" << setw(15) << hash->key << 
	//			" Count:" << hash->value << endl;
}

typedef enum {
	NAME_INPUT		= (0x1 << 0),
	PASS1_INPUT		= (0x1 << 1),
	PASS2_INPUT		= (0x1 << 2),
	EMAIL_INPUT		= (0x1 << 3),
} DEV_INPUT_MODES;

void CLTUI::GetDevFields (int mode) {
	char field[31];
	
	if (mode & EMAIL_INPUT) {
		cout << "EMAIL: ";
		cin.getline(field,31);
		Dev.email.set(field);
	}
	
	if (mode & NAME_INPUT) {
		cout << "NAME: ";
		cin.getline(field,31);
		Dev.name.set(field);
	}
	
	if (mode & PASS1_INPUT) {
		cout << "PASSWORD: ";
		cin.getline(field,31);
		Dev.password.set(field);
	}
	
	if (mode & PASS2_INPUT) {
		cout << "PASSWORD: ";
		cin.getline(field,31);
		Pass.set(field);
		
		if (Dev.password.get().compare(Pass.get()))
			throw invalid_argument("PASSWORDS NOT MATCHING");
	}
}

void CLTUI::Parse_Developer () {
	if (Word == "add") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDevFields(	NAME_INPUT |
								EMAIL_INPUT |
								PASS1_INPUT |
								PASS2_INPUT);
				
				CONTROLLER::instance()->AddDeveloper(Dev);
				
				cout << ctab << "USER ADDED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "name") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDevFields(	NAME_INPUT);
				
				CONTROLLER::instance()->EditDevName(Dev.name);
				
				cout << ctab << "USER NAME EDITED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "password") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDevFields(	PASS1_INPUT |
								PASS2_INPUT);
				
				CONTROLLER::instance()->EditDevPassword(Dev.password);
				
				cout << ctab << "USER PASSWORD EDITED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "remove") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDevFields(	EMAIL_INPUT );
				
				CONTROLLER::instance()->RemoveDeveloper(Dev.email);
				
				cout << ctab << "USER REMOVED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	SuggestManual();
}

void CLTUI::Parse_Project () {
	if (Word == "assign") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDevFields(	EMAIL_INPUT );
				
				CONTROLLER::instance()->ProjectAssign(Dev.email);
				
				cout << ctab << "NEW ADMINISTRATOR ASSIGNED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	SuggestManual();
}

typedef enum {
	PROD_NAME		= (0x1 << 0),
	CODE_INPUT		= (0x1 << 1),
	PROD_VERSION	= (0x1 << 2),
	PROD_STATE		= (0x1 << 2)
} PROD_INPUT_MODES;

void CLTUI::GetProdFields (int mode) {
	char field[31];
	
	if (mode & PROD_NAME) {
		cout << "PRODUCT NAME: ";
		cin.getline(field,31);
		Prod.name = field;
	}
	
	if (mode & CODE_INPUT) {
		cout << "PRODUCT CODE: ";
		cin.getline(field,31);
		Prod.id_code.set(field);
	}
	
	if (mode & PROD_VERSION) {
		cout << "PRODUCT VERSION: ";
		cin.getline(field,31);
		Prod.version.set(field);
	}
}

void CLTUI::Parse_Product () {
	if (Word == "add") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetProdFields(	PROD_NAME |
								CODE_INPUT |
						 		PROD_VERSION);
				
				CONTROLLER::instance()->AddProduct(Prod);
				
				cout << ctab << "NEW PRODUCT REGISTERED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "name") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetProdFields(	PROD_NAME |
								CODE_INPUT);
				
				CONTROLLER::instance()->EditProductName(Prod);
				
				cout << ctab << "NEW PRODUCT REGISTERED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "version") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetProdFields(	CODE_INPUT |
						 		PROD_VERSION);
				
				CONTROLLER::instance()->EditProductVersion(Prod);
				
				cout << ctab << "NEW PRODUCT REGISTERED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "assign") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetProdFields(	CODE_INPUT);
				GetDevFields(	EMAIL_INPUT);
				
				CONTROLLER::instance()->AssignDevProduct(Dev, Prod);
				
				cout << ctab << "DEVELOPER ASSIGNED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "remove") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetProdFields(	CODE_INPUT);
				
				CONTROLLER::instance()->RemoveProduct(Prod);
				
				cout << ctab << "PRODUCT REMOVED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "list") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				list<Product> Products = CONTROLLER::instance()->ListProducts();
				
				if (Products.empty())
					cout << ctab << "NÃO HÁ PRODUTOS CADASTRADOS";
				
				while (! Products.empty()) {
					Prod = Products.back();
					Products.pop_back();
					cout 	<< ctab << Prod.name << endl
							<< ctab << ctab << Prod.id_code.get() << endl
							<< ctab << ctab << Prod.version.get() << endl
							<< ctab << ctab << Prod.developer.get() << endl;
				}
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (! Word.Null()) SuggestManual();
}

typedef enum {
	DEFC_NAME		= (0x1 << 0),
	D_DESCRIPTION	= (0x1 << 1),
	D_CODE_INPUT	= (0x1 << 2),
	D_STATE_INPUT	= (0x1 << 2)
} DEFC_INPUT_MODES;

void CLTUI::GetDefcFields (int mode) {
	char field[31];
	
	if (mode & DEFC_NAME) {
		cout << "DEFECT NAME: ";
		cin.getline(field,31);
		Defct.name = field;
	}
	
	if (mode & D_DESCRIPTION) {
		cout << "DEFECT DESCRIPTION: ";
		cin.getline(field,31);
		Defct.description = field;
	}
	
	if (mode & D_CODE_INPUT) {
		cout << "DEFECT CODE: ";
		cin.getline(field,31);
		Defct.id_code.set(field);
	}
	
	if (mode & D_STATE_INPUT) {
		cout << "DEFECT STATE: ";
		cin.getline(field,31);
		Defct.state = field;
	}
}

void CLTUI::Parse_Defect () {
	if (Word == "add") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDefcFields(	DEFC_NAME |
								D_DESCRIPTION |
								D_CODE_INPUT );
				GetProdFields( CODE_INPUT );
				
				CONTROLLER::instance()->AddDefect(Prod, Defct);
				
				cout << ctab << "NEW DEFECT REGISTERED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "name") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDefcFields(	DEFC_NAME |
								D_CODE_INPUT );
				
				CONTROLLER::instance()->EditDefectName(Defct);
				
				cout << ctab << "DEFECT NAME EDITED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "description") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDefcFields(	D_DESCRIPTION |
								D_CODE_INPUT );
				
				CONTROLLER::instance()->EditDefectDescription(Defct);
				
				cout << ctab << "DEFECT DESCRIPTION EDITED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "state") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDefcFields(	D_STATE_INPUT |
								D_CODE_INPUT );
				
				CONTROLLER::instance()->EditDefectState(Defct);
				
				cout << ctab << "DEFECT STATE EDITED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "vote") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDefcFields(	D_CODE_INPUT );
				
				CONTROLLER::instance()->EditDefectVotes(Defct);
				
				cout << ctab << "DEFECT STATE EDITED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "assign") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDefcFields(	D_CODE_INPUT );
				GetDevFields(	EMAIL_INPUT);
				
				CONTROLLER::instance()->AssignDevDefect(Dev, Defct);
				
				cout << ctab << "DEFECT ASSIGNED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "candidate") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDefcFields(	D_CODE_INPUT );
				
				CONTROLLER::instance()->OfferAsCandidate(Defct);
				
				cout << ctab << "CANDIDATED TO DEFECT";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "remove") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetDefcFields(	D_CODE_INPUT );
				
				CONTROLLER::instance()->CloseDefect(Defct);
				
				cout << ctab << "DEFECT CLOSED";
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (Word == "list") {
		if (! Word.Null()) SuggestManual();
		else {
			try {
				GetProdFields( CODE_INPUT );
				
				list<Defect> Defects = CONTROLLER::instance()->ListDefects(Prod);
				
				if (Defects.empty())
					cout << ctab << "NÃO HÁ DEFEITOS CADASTRADOS NESTE PRODUTO";
				
				while (! Defects.empty()) {
					Defct = Defects.back();
					Defects.pop_back();
					cout 	<< ctab << Defct.name << ctab << Defct.id_code.get() << endl
							<< ctab << "DESCR" << ctab << Defct.description << endl
							<< ctab << "DEVEL" << ctab << Defct.developer.get() << endl
							<< ctab << "VOTES" << ctab << Defct.votes << endl
							<< ctab << "STATE" << ctab << Defct.state << endl
							<< ctab << "OPENI" << ctab << Defct.opening << endl
							<< ctab << "CLOSE" << ctab << Defct.closing << endl;
				}
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
			Word++;
		}
	}
	else
	
	if (! Word.Null()) SuggestManual();
}

void CLTUI::Parse () {
	// QUIT PROGRAM
	if ((Word == "quit") || 
		(Word == "q")) {
		if (Word.Str()) SuggestManual();
		else throw QUIT_APP;
	} else
	
	// UNIT TEST
	if ((Word == "test") || 
		(Word == "tst")) {
		if (Word.Null()) TESTENVIROMENT::instance()->RunTests();
		else SuggestManual();
	} else
	
	// LOGOUT
	if (Word == "logout") {
		if (Word.Null()) {
			CONTROLLER::instance()->Logout();
			cout << ctab << "USER LOGGED OUT";
		}
		else SuggestManual();
	} else
	
	// DEVELOPER ACTIONS
	if ((Word == "dev") || 
		(Word == "developer")) Parse_Developer();
	else
	
	// PROJECT ACTIONS
	if ((Word == "proj") || 
		(Word == "project")) Parse_Project();
	else
	
	// PRODUCT ACTIONS
	if ((Word == "prod") || 
		(Word == "product")) Parse_Product();
	else
	
	// ISSUE ACTIONS
	if (Word == "defect") Parse_Defect();
	else
	
	// SHOW HELP
	if ((Word == "?") || 
		(Word == "help") ) {
			if (Word.Null()) {
				PrintFile("manual.txt");
			}
			else SuggestManual();
		}
	else
	
	{
		if (Word.Str()) SuggestManual();
	}
	
	if (Word.Null()) Word++;
}

void CLTUI::Run () {
	while (true) {
		if (CONTROLLER::instance()->Initialize() == false) {
			try {
				cout << "INITIATE ADMIN USER" << endl;
				GetDevFields(	NAME_INPUT |
								EMAIL_INPUT |
								PASS1_INPUT |
								PASS2_INPUT);
				CONTROLLER::instance()->Initialize(Dev);
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
		} else
		
		if (CONTROLLER::instance()->User() == false) {
			try {
				cout << "LOG INTO REVISIONS" << endl;
				GetDevFields(	EMAIL_INPUT |
								PASS1_INPUT);
				CONTROLLER::instance()->User(Dev);
			}
			catch (invalid_argument error) {
				cout << ctab << error.what();
			}
		} else 
		
		if (Word.Str()) {
			Parse();
			cout << endl;
		}
		else {
			cout << CONTROLLER::instance()->Scope();
			Word.Set();
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
	
	return p_instance;
}

MethaUI * MethaUI::instance () {
	if (p_instance) return p_instance;
	return instance (0);
}
