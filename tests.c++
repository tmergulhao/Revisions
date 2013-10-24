#include <string.h>

#include <iostream>
using namespace std;

#include "tests.h"

void TestTypes::RightName () {
	char * sample = new char [31];
	strcpy (sample,"Tiago Mergulhao");
	
	try {
		dev_name->set(sample);
	}
	catch (dev_name_error error) {
		cout << "!!" << "\t\t" << "RIGHT NAME TEST" << endl;
		return;
	}
	cout << "OK" << "\t\t" << "RIGHT NAME TEST" << endl;
}
void TestTypes::WrongName () {
	char * sample = new char [31];
	strcpy (sample,"Tiago 1");
	
	try {
		dev_name->set(sample);
	}
	catch (dev_name_error error) {
		cout << "OK" << "\t\t" << "WRONG NAME TEST" << endl;
		return;
	}
	cout << "!!" << "\t\t" << "WRONG NAME TEST" << endl;
}

void TestTypes::RightEmail () {
	char * sample = new char [100];
	strcpy (sample,"me@tmergulhao.com");
	
	try {
		email->set (sample);
	}
	catch (email_error error) {
		cout << "!!" << "\t\t" << "RIGHT EMAIL TEST" << endl;
		return;
	}
	cout << "OK" << "\t\t" << "RIGHT EMAIL TEST" << endl;
}
void TestTypes::WrongEmail () {
	char * sample = new char [100];
	strcpy (sample,"me@.tmergulhao.com");
	
	try {
		email->set (sample);
	}
	catch (email_error error) {
		cout << "OK" << "\t\t" << "WRONG EMAIL TEST" << endl;
		return;
	}
	cout << "!!" << "\t\t" << "WRONG EMAIL TEST" << endl;
}

void TestTypes::RightPassword () {
	char * sample = new char [7];
	strcpy (sample,"12345");
	
	try {
		password->set (sample);
	}
	catch (email_error error) {
		cout << "!!" << "\t\t" << "RIGHT PASSWORD TEST" << endl;
		return;
	}
	cout << "OK" << "\t\t" << "RIGHT PASSWORD TEST" << endl;
}
void TestTypes::WrongPassword_EQUAL () {
	char * sample = new char [7];
	strcpy (sample,"12344");
	
	try {
		password->set (sample);
	}
	catch (password_error error) {
		
		if (error == EQUAL_CHARS)
			cout << "OK" << "\t\t" << "WRONG PASSWORD EQUAL TEST" << endl;
		return;
	}
	cout << "!!" << "\t\t" << "WRONG PASSWORD EQUAL TEST" << endl;
}

void TestTypes::WrongPassword_SIZE () {
	char * sample = new char [7];
	strcpy (sample,"1234");
	
	try {
		password->set (sample);
	}
	catch (password_error error) {
		
		if (error == INVALID_SIZE)
			cout << "OK" << "\t\t" << "WRONG PASSWORD SIZE TEST" << endl;
		return;
	}
	cout << "!!" << "\t\t" << "WRONG PASSWORD SIZE TEST" << endl;
}

void TestTypes::MatchPassword () {
	char sample1 [] = "abcde";
	char sample2 [] = "abcde";
	
	try {
		password->set ((char *)&sample1);
		password_second->set((char *)&sample2);
		((*password_second) == (*password));
	}
	catch (password_matching matching) {
		if (matching == EQUAL) {
			cout << "OK" << "\t\t" << "PASSWORD MATCH TEST" << endl;
			return;
		}
		if (matching == NOT_EQUAL) {
			cout << "!1" << "\t\t" << "PASSWORD MATCH TEST" << endl;
			return;
		}
	}
	catch (password_error error) {
		if (error == INVALID_SIZE) cout << "INVALID SIZE";
		if (error == EQUAL_CHARS) cout << "EQUAL CHARS";
		return;
	}
}

void TestTypes::NotMatchPassword () {
	char sample1 [] = "abcde";
	char sample2 [] = "abcdf";
	
	try {
		password->set ((char *)&sample1);
		password_second->set((char *)&sample2);
		((*password_second) == (*password));
	}
	catch (password_matching matching) {
		if (matching == EQUAL) {
			cout << "!1" << "\t\t" << "PASSWORD NO MATCH TEST" << endl;
			return;
		}
		if (matching == NOT_EQUAL) {
			cout << "OK" << "\t\t" << "PASSWORD NO MATCH TEST" << endl;
			return;
		}
	}
	catch (password_error error) {
		if (error == INVALID_SIZE) cout << "INVALID SIZE";
		if (error == EQUAL_CHARS) cout << "EQUAL CHARS";
		return;
	}
}

TestTypes::TestTypes () {
	dev_name = new class dev_name;
	email = new class email;
	password = new class password;
	password_second = new class password;
}
void TestTypes::RunTests () {
	this->RightName();
	this->WrongName();
	
	this->RightEmail();
	this->WrongEmail();
	
	this->RightPassword();
	this->WrongPassword_EQUAL();
	this->WrongPassword_SIZE();
	this->MatchPassword();
	this->NotMatchPassword();
}
TestTypes::~TestTypes () {
	delete dev_name;
	delete email;
	delete password;
	delete password_second;
}

class TestingEnviroment * TestingEnviroment::p_instance = 0;

TestingEnviroment::TestingEnviroment () {
	TestTypes = new class TestTypes;
}
TestingEnviroment::~TestingEnviroment () {
	delete TestTypes;
}