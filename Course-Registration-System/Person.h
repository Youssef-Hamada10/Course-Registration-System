#pragma once
#include <string>

using namespace std;

class Person
{
protected:
	string ID;
	string username;
	string password;

public:
	Person(string ID, string username, string password);
	Person();
	void setID(string);
	string getID();
	string getUsername();
	void setUsername(string username);
	string getPassword();
	void setPassword(string password);
	//virtual pair<bool, map<string, Person>> login(Person* user) = 0;
};

