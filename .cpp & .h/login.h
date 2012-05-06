#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::getline;
using std::string;

#include <fstream>
using std::fstream;
using std::ios;

#include <vector>
using std::vector;

#include <limits>
using std::numeric_limits;
using std::streamsize;
using std::max;

#include <stdio.h>
using std::remove;

class LogIn
{
private:
	string fileName;
	string userFileName;
	string passFileName;
	fstream file;
	
	string encrypt(string);
	string decrypt(string);

protected:
	int choice;
	int pos;
	string user;
	string pass;
	string delUser;
	vector<string> password;
	vector<string> username;

	void errorMessage();
	void vectorSizeCheck();
	void openFileCheck();

public:
	LogIn();
	~LogIn();

	// Miscallaneous fucntions
	virtual void mainMenu();
	void menuChoices();
	void deleteQuery();
	void displayContents();
	void createAccount();
	virtual int inputValidation(string, int, int);

	// Find if user is in the system.
	void getUserInfo();
	bool findUserName();
	bool findPassWord();

	// Load and save data from file.
	void loadAccounts();
	void saveAccounts();
	void deleteAccount();
};
#endif