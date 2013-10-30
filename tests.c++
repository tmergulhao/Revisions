#include <string.h>

#include <iostream>
using namespace std;
#define	ctab	"\t"

#include "tests.h"

class TestTypes {
		static class TestTypes * p_instance;
		
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
		
		static TestTypes * instance () {
			if (p_instance) return p_instance;
			return p_instance = new class TestTypes();
		}
}; typedef class TestTypes TSTTYPES;

//SINGULARIZATION
/////////////////

TestTypes * TestTypes::p_instance = 0;

TestTypes::TestTypes () {
	dev_name = new class dev_name;
	email = new class email;
	password = new class password;
	password_second = new class password;
}
void TestTypes::RunTests () {
	RightName();
	WrongName();
	
	RightEmail();
	WrongEmail();
	
	RightPassword();
	WrongPassword_EQUAL();
	WrongPassword_SIZE();
	MatchPassword();
	NotMatchPassword();
}
TestTypes::~TestTypes () {
	delete dev_name;
	delete email;
	delete password;
	delete password_second;
}

void TestTypes::RightName () {
	try {
		dev_name->set("Tiago Mergulhao");
	}
	catch (dev_name_error error) {
		cout << "!!" << ctab << ctab << "RIGHT NAME TEST" << endl;
		return;
	}
	cout << "OK" << ctab << ctab << "RIGHT NAME TEST" << endl;
}
void TestTypes::WrongName () {
	try {
		dev_name->set("Tiago 1");
	}
	catch (dev_name_error error) {
		cout << "OK" << ctab << ctab << "WRONG NAME TEST" << endl;
		return;
	}
	cout << "!!" << ctab << ctab << "WRONG NAME TEST" << endl;
}

void TestTypes::RightEmail () {
	try {
		email->set ("me@tmergulhao.com");
	}
	catch (email_error error) {
		cout << "!!" << ctab << ctab << "RIGHT EMAIL TEST" << endl;
		return;
	}
	cout << "OK" << ctab << ctab << "RIGHT EMAIL TEST" << endl;
}
void TestTypes::WrongEmail () {
	try {
		email->set ("me@.tmergulhao.com");
	}
	catch (email_error error) {
		cout << "OK" << ctab << ctab << "WRONG EMAIL TEST" << endl;
		return;
	}
	cout << "!!" << ctab << ctab << "WRONG EMAIL TEST" << endl;
}

void TestTypes::RightPassword () {
	try {
		password->set ("12345");
	}
	catch (email_error error) {
		cout << "!!" << ctab << ctab << "RIGHT PASSWORD TEST" << endl;
		return;
	}
	cout << "OK" << ctab << ctab << "RIGHT PASSWORD TEST" << endl;
}
void TestTypes::WrongPassword_EQUAL () {
	try {
		password->set ("12344");
	}
	catch (password_error error) {
		
		if (error == EQUAL_CHARS)
			cout << "OK" << ctab << ctab << "WRONG PASSWORD EQUAL TEST" << endl;
		return;
	}
	cout << "!!" << ctab << ctab << "WRONG PASSWORD EQUAL TEST" << endl;
}

void TestTypes::WrongPassword_SIZE () {
	try {
		password->set ("1234");
	}
	catch (password_error error) {
		
		if (error == INVALID_SIZE)
			cout << "OK" << ctab << ctab << "WRONG PASSWORD SIZE TEST" << endl;
		return;
	}
	cout << "!!" << ctab << ctab << "WRONG PASSWORD SIZE TEST" << endl;
}

void TestTypes::MatchPassword () {
	password->set ("abcde");
	password_second->set("abcde");
	
	if ((*password_second) == (*password)) 
		cout << "OK" << ctab << ctab << "PASSWORD MATCH TEST" << endl;
	else 
		cout << "!!" << ctab << ctab << "PASSWORD MATCH TEST" << endl;
}

void TestTypes::NotMatchPassword () {
	password->set ("abcde");
	password_second->set("abcdf");
	
	if ((*password_second) == (*password)) 
		cout << "!!" << ctab << ctab << "PASSWORD MATCH TEST" << endl;
	else 
		cout << "OK" << ctab << ctab << "PASSWORD MATCH TEST" << endl;
}

//SINGULARIZATION
/////////////////

TestingEnviroment * TestingEnviroment::p_instance = 0;

TestingEnviroment * TestingEnviroment::instance () {
	if (p_instance) return p_instance;
	return p_instance = new class TestingEnviroment ();
}

void TestingEnviroment::RunTests () {
	TSTTYPES::instance()->RunTests();
}
TestingEnviroment::~TestingEnviroment () {
	delete TSTTYPES::instance();
}
