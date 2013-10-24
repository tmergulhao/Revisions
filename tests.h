#ifndef TESTS_H
#define TESTS_H

#include "basetypes.h"

class TestTypes {
		dev_name* dev_name;
		email* email;
		class password* password;
		class password* password_second;
	public:
		TestTypes();
		~TestTypes();
		
		void RunTests();
		
		void RightName();
		void WrongName();
		
		void RightEmail();
		void WrongEmail();
		
		void RightPassword();
		void WrongPassword_SIZE();
		void WrongPassword_EQUAL();
		void MatchPassword();
		void NotMatchPassword();
};

class TestingEnviroment {
		static class TestingEnviroment * p_instance;
	public:
		TestTypes* TestTypes;
		
		TestingEnviroment();
		~TestingEnviroment();
		
		static TestingEnviroment * instance () {
			if (p_instance) return p_instance;
			return (p_instance = new class TestingEnviroment());
		}
}; typedef class TestingEnviroment TESTENVIROMENT;

#endif