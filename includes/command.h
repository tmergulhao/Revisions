#ifndef COMMAND_H
#define COMMAND_H

#include <basetypes.h>
#include <controller.h>

#include <stdio.h>

#include <iostream>
using namespace std;
#define	ctab	"\t"

class MethaUI {
		static MethaUI * p_instance;
	public:
		virtual void Run () {}
		
		MethaUI () {}
		MethaUI (int);
		
		virtual ~MethaUI () {}
		
		static MethaUI * instance (int);
		static MethaUI * instance ();
};typedef class MethaUI USRINTERFACE;

#endif
