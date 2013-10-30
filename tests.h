#ifndef TESTS_H
#define TESTS_H

#include "basetypes.h"

class TestingEnviroment {
		static class TestingEnviroment * p_instance;
	public:
		void RunTests();
		
		TestingEnviroment() {}
		~TestingEnviroment();
		
		static TestingEnviroment * instance ();
}; typedef class TestingEnviroment TESTENVIROMENT;

#endif
