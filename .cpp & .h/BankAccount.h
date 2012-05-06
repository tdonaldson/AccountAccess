#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "LogIn.h"

#include <iomanip>
using std::setprecision;
using std::fixed;
using std::showpoint;
using std::ostream;

// Structure to hold all the account
// information of the client.
struct AccountInfo
{
	string name;
	string address;
	string city;
	string accountType;
	string creationDate;
	string phoneNumber;
	double balance;
	double lastWithdrawal;
	double lastDeposit;

	AccountInfo()
	{
		name = "dummy";
		address = "123 begin lane";
		city = "doesn't exist";
		phoneNumber = "111-222-3333";
		accountType = "none";
		creationDate = "never";
		balance = 0;
		lastWithdrawal = 0;
		lastDeposit = 0;
	}
};

class BankAccount : public LogIn
{
private:
	string name;
	string fileName;
	fstream file;
	int choice;
	AccountInfo acctInfo;
	double newWithdrawal;
	double newDeposit;

public:
	// Constructor and destructor.
	BankAccount(string);
	~BankAccount();

	// Menu display and choice.
	void BankAccountMenu();
	void BankAccountChoice();

	// Display functions.
	void displayOwner();
	void displayBalance();
	void displayCreationDay();

	// File loading and saving.
	void loadFile();
	void saveFile();
	void updateStatement(string, double);

	// Editting functions.
	void newAccount();
	void editOwner();
	void enterDeposit();
	void enterWithdrawal();
	void editCreationDay();

	friend ostream &operator<<(ostream &, AccountInfo &);
	void operator=(AccountInfo &r);
};
#endif