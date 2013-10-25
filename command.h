#ifndef COMMAND_H
#define COMMAND_H

#include "basetypes.h"

typedef enum {
	QUIT_APPLICATION = 0, VIEW_MANUAL, SUGEST_MANUAL
} AppStates;

class MethaUI {
	public:
		class Developer * Dev;
		class password * password;
		virtual void Run () = 0;
		//virtual void GetOpt () = 0;
		//virtual void GetField () = 0;
};

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
		bool operator!= (const char * sample);
		bool operator++ (int);
};

typedef enum {
	EMAIL_INPUT		= (0x1 << 0),
	NAME_INPUT		= (0x1 << 1),
	PASS1_INPUT		= (0x1 << 2),
	PASS2_INPUT		= (0x1 << 3),
	ID_INPUT		= (0x1 << 4),
	STATE_INPUT		= (0x1 << 5)
} INPUT_MODES;

class CLTUI: public MethaUI {
		class CommandWord * Word;
	public:
		CLTUI () {
			Word = new class CommandWord;
			Dev = new class Developer;
			password = new class password;
		}
		
		void Run();
		void ParseOpt ();
		void PrintScope ();
		void PrintFile (const char *);
		
		void GetFields (int);
		
		~CLTUI () {
			delete Word;
			delete Dev;
			delete password;
		}
};

#endif
