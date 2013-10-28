#include <string.h>

#include <iostream>
using namespace std;

#include "tests.h"

void TestTypes::RightName () {
	try {
		dev_name->set("Tiago Mergulhao");
	}
	catch (dev_name_error error) {
		cout << "!!" << "\t\t" << "RIGHT NAME TEST" << endl;
		return;
	}
	cout << "OK" << "\t\t" << "RIGHT NAME TEST" << endl;
}
void TestTypes::WrongName () {
	try {
		dev_name->set("Tiago 1");
	}
	catch (dev_name_error error) {
		cout << "OK" << "\t\t" << "WRONG NAME TEST" << endl;
		return;
	}
	cout << "!!" << "\t\t" << "WRONG NAME TEST" << endl;
}

void TestTypes::RightEmail () {
	try {
		email->set ("me@tmergulhao.com");
	}
	catch (email_error error) {
		cout << "!!" << "\t\t" << "RIGHT EMAIL TEST" << endl;
		return;
	}
	cout << "OK" << "\t\t" << "RIGHT EMAIL TEST" << endl;
}
void TestTypes::WrongEmail () {
	try {
		email->set ("me@.tmergulhao.com");
	}
	catch (email_error error) {
		cout << "OK" << "\t\t" << "WRONG EMAIL TEST" << endl;
		return;
	}
	cout << "!!" << "\t\t" << "WRONG EMAIL TEST" << endl;
}

void TestTypes::RightPassword () {
	try {
		password->set ("12345");
	}
	catch (email_error error) {
		cout << "!!" << "\t\t" << "RIGHT PASSWORD TEST" << endl;
		return;
	}
	cout << "OK" << "\t\t" << "RIGHT PASSWORD TEST" << endl;
}
void TestTypes::WrongPassword_EQUAL () {
	try {
		password->set ("12344");
	}
	catch (password_error error) {
		
		if (error == EQUAL_CHARS)
			cout << "OK" << "\t\t" << "WRONG PASSWORD EQUAL TEST" << endl;
		return;
	}
	cout << "!!" << "\t\t" << "WRONG PASSWORD EQUAL TEST" << endl;
}

void TestTypes::WrongPassword_SIZE () {
	try {
		password->set ("1234");
	}
	catch (password_error error) {
		
		if (error == INVALID_SIZE)
			cout << "OK" << "\t\t" << "WRONG PASSWORD SIZE TEST" << endl;
		return;
	}
	cout << "!!" << "\t\t" << "WRONG PASSWORD SIZE TEST" << endl;
}

void TestTypes::MatchPassword () {
	password->set ("abcde");
	password_second->set("abcde");
	
	if ((*password_second) == (*password)) 
		cout << "OK" << "\t\t" << "PASSWORD MATCH TEST" << endl;
	else 
		cout << "!!" << "\t\t" << "PASSWORD MATCH TEST" << endl;
}

void TestTypes::NotMatchPassword () {
	password->set ("abcde");
	password_second->set("abcdf");
	
	if ((*password_second) == (*password)) 
		cout << "!!" << "\t\t" << "PASSWORD MATCH TEST" << endl;
	else 
		cout << "OK" << "\t\t" << "PASSWORD MATCH TEST" << endl;
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