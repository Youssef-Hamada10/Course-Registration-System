#include <string>

using namespace std;

class Person {
protected:
	string username;
	string password;

public:
	Person(string username, string password);
	Person();
	string getUsername();
	void setUsername(string username);
	string getPassword();
	void setPassword(string password);
};
