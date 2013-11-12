#ifndef TESTS_H
#define TESTS_H

class TestingEnviroment {
		static class TestingEnviroment * p_instance;
	public:
		void RunTests();
		
		TestingEnviroment() {}
		~TestingEnviroment();
		
		static TestingEnviroment * instance ();
}; typedef class TestingEnviroment TESTENVIROMENT;

#endif
