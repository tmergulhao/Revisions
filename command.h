#ifndef COMMAND_H
#define COMMAND_H

typedef enum {
	QUIT_APPLICATION = 0, VIEW_MANUAL, SUGEST_MANUAL
} AppStates;

class MethaUI {
	public:
		virtual void Run () = 0;
		//virtual void GetOpt () = 0;
		//virtual void GetField () = 0;
};

class CLTUI: public MethaUI {
		class CommandWord * Word;
		
	public:
		CLTUI ();
		
		void Run();
		void ParseOpt ();
		void PrintScope ();
		void PrintFile (const char *);
		
		~CLTUI ();
};

#endif
