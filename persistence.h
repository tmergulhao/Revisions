#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <sqlite3.h>

#include "basetypes.h"

class SQLInterface {
		static SQLInterface * p_instance;
	public:
		// USER
		// VALIDATE DEVELOPER LOGIN
		virtual bool Login (Developer *) { return 0; }
		
		// CHANGES DEVELOPER DATA
		//virtual bool ChangeUser (Developer *) = 0;
		
		// PRODUCT
		// STARTS NEW PRODUCT
		//virtual bool NewProduct (methaproject *) = 0;
		// SWITCHES PRODUCT STATE
		//virtual bool ChangeState (methaproject_states) = 0;
		
		// ISSUE
		// STARTS NEW ISSUE
		//virtual bool NewIssue (methaproject *, methaproject *) = 0;
		// SWITCHES PRODUCT STATE
		//virtual bool ChangeState (product *, methaproject_states) = 0;
		
		// SWITCHES ISSUE STATE
		//virtual bool ChangeState (defect *, methaproject_states) = 0;
		
		SQLInterface () {}
		SQLInterface (int);
		
		virtual ~SQLInterface () {}
		
		static SQLInterface * instance (int);
		static SQLInterface * instance ();
};typedef class SQLInterface SQLINTERFACE;

#endif
