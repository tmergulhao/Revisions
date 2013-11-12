#ifndef CONSTROLLER_H
#define CONSTROLLER_H

#include <sqlite3.h>

#include <entities.h>

class Controller {
		static Controller * p_instance;
	public:
		virtual bool Login (Developer *) { return 0; }
		
		Controller () {}
		Controller (int);
		
		virtual ~Controller () {}
		
		static Controller * instance (int);
		static Controller * instance ();
};typedef class Controller CONTROLLER;

#endif
