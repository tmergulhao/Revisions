#ifndef COMMAND_H
#define COMMAND_H

#include "basetypes.h"
#include "persistence.h"

#include <stdio.h>

class MethaUI {
		static MethaUI * p_instance;
	public:
		virtual void Run () = 0;
		
		MethaUI () {}
		MethaUI (int);
		
		static MethaUI * instance (int);
		static MethaUI * instance () {
			return p_instance;
		}
};

#endif
