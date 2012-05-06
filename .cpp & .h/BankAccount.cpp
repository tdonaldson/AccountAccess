#include "BankAccount.h"

// Constructor that excepts the username. 
// The fileName is a data file with the same name
// as the username.
BankAccount::BankAccount(string user)
{
	this->name = user;
	fileName = user + ".dat";
	loadFile();
}

// Destructor for the bank account.
BankAccount::~BankAccount()
{	
	if (file.is_open())
		file.close();
}

// Displays the menu for the bank account.
void BankAccount::BankAccountMenu()
{
	cout << "----------------\n";
	cout << "--BANK ACCOUNT--\n";
	cout << "----------------\n";
	cout << "1. Owner\n";
	cout << "2. Balance\n";
	cout << "3. Date Created\n";
	cout << "4. New Deposit\n";
	cout << "5. New Withdrawal\n";
	cout << "9. LogOut\n";
	choice = LogIn::inputValidation("Choice", 1, 5);
	BankAccountChoice();
}

// This function gets the information of the client if this 
// is their first day as a customer.
// Also creates the file for the bank statement. Will insert
// the initial deposit into the statement.
void BankAccount::newAccount()
{
	cout << "Press enter to continue.\n";
	cin.get();
	cout << "Enter your name: ";
	getline(cin, acctInfo.name);
	cout << "Enter your address: ";
	getline(cin, acctInfo.address);
	cout << "Enter your city/state/zip: ";
	getline(cin, acctInfo.city);
	cout << "Enter your account type: ";
	getline(cin, acctInfo.accountType);
	cout << "Enter today's date: ";
	getline(cin, acctInfo.creationDate);
	cout << "Enter your phone number: ";
	getline(cin, acctInfo.phoneNumber);
	cout << "Enter the initial deposit: ";
	cin >> acctInfo.balance;
	acctInfo.lastDeposit = acctInfo.balance;
	acctInfo.lastWithdrawal = 0;
	saveFile();

	updateStatement("Initial Deposit", acctInfo.lastDeposit);
	BankAccountMenu();
}

void BankAccount::displayOwner()
{
	cout << "\nThe owner of the account is: " << acctInfo.name << endl;
	cout << "The address of the owner is: " << acctInfo.address << endl;
	cout << "The telephone number is:     " << acctInfo.phoneNumber << "\n\n";
}

void BankAccount::displayBalance()
{
	cout << "\nThe balance of the account is: $" << acctInfo.balance << endl;
	cout << "The amount of the last deposit was: $" << acctInfo.lastDeposit << endl;
	cout << "The amount of the last withdrawal was: $" << acctInfo.lastWithdrawal << "\n\n";
}

void BankAccount::displayCreationDay()
{
	cout << "\nThis account has been active since " << acctInfo.creationDate << "\n\n";
}

// Gets the newest deposit of the account.
// Will save the newest deposit to the account holders
// data file and then will save it to the user's
// bank statement text file.
void BankAccount::enterDeposit()
{
	cout << "\nEnter the amount of the deposit: $";
	cin >> newDeposit;
	acctInfo.lastDeposit = newDeposit;
	acctInfo.balance += acctInfo.lastDeposit;
	saveFile();
	cout << endl;

	updateStatement("Deposit", newDeposit);
}

// Gets the newest withdrawal of the account.
// Will save the newest deposit to the account holders
// data file and then will save it to the user's
// bank statement text file.
void BankAccount::enterWithdrawal()
{
	cout << "\nEnter the amount of the withdrawal: $";
	cin >> newWithdrawal;
	acctInfo.lastWithdrawal = newWithdrawal;
	acctInfo.balance -= acctInfo.lastWithdrawal;
	saveFile();
	cout << endl;

	updateStatement("Withdraw", newWithdrawal);
}

void BankAccount::BankAccountChoice()
{
	switch (choice)
	{
	case 1:
		displayOwner();
		break;
	case 2:
		displayBalance();
		break;
	case 3:
		displayCreationDay();
		break;
	case 4:
		enterDeposit();
		break;
	case 5:
		enterWithdrawal();
		break;
	case 9: 
		cout << "\nYou have successfully logged out.\n\n";
		saveFile();
		system("cls");
		LogIn::mainMenu();
		break;
	}

	BankAccountMenu();
}

// Loads the file of the client.
void BankAccount::loadFile()
{
	file.open(fileName, ios::in);
	char answer;

	// Iterates if the bank doesn't have a file
	// associated with the client.
	if (!file)
	{
		cout << "File does not exist.\n";
		cout << "Do you wish to create your file? (Y/N) ";
		cin >> answer;

		// Iterates if the bank wants to create a file.
		if (toupper(answer) == 'Y')
		{	
			file.open(fileName, ios::out);
			file.close();

			newAccount();
		}

		// Else iterates if the bank does NOT want to
		// create a file for the client.
		else
		{
			cout << "Reverting to main menu.\n";
			LogIn::mainMenu();
		}	
	}


	// This iterates if the file exists.
	else
	{
		AccountInfo temp;

		getline(file, temp.name, '\n');
		getline(file, temp.address, '\n');
		getline(file, temp.city, '\n');
		getline(file, temp.accountType, '\n');
		getline(file, temp.creationDate, '\n');
		getline(file, temp.phoneNumber, '\n');
		file >> temp.balance;
		file >> temp.lastWithdrawal;
		file >> temp.lastDeposit;

		acctInfo = temp;

		file.close();
	}
}

// Saves the account information to the file.
void BankAccount::saveFile()
{
	file.open(fileName, ios::out);

	file << acctInfo.name << endl;
	file << acctInfo.address << endl;
	file << acctInfo.city << endl;
	file << acctInfo.accountType << endl;
	file << acctInfo.creationDate << endl;
	file << acctInfo.phoneNumber << endl;
	file << acctInfo.balance << endl;
	file << acctInfo.lastWithdrawal << endl;
	file << acctInfo.lastDeposit << endl;

	file.close();
}

// Updates the user's bank statement. This file will only 
// ever be written to, never to be opened within the program.
void BankAccount::updateStatement(string mes, double val)
{
	string temp = acctInfo.name + ".dat";
	mes += ": ";
	file.open(temp, ios::out | ios::app);
	file << endl << mes << val;
	file.close();
}

// Overloaded extraction operator for AccountInfo structure.
ostream &operator<<(ostream &out, AccountInfo &acct)
{
	out << "Name: " << acct.name << endl;
	out << "Address: " << acct.address << endl;
	out << "Location: " << acct.city << endl;
	out << "Phone Number: " << acct.phoneNumber << endl;
	out << "Account Type: " << acct.accountType << endl;
	out << "Creation Date: " << acct.creationDate << endl;
	out << "Balance: $" << fixed << setprecision(2) << acct.balance << endl;
	out << "Last Withdrawal: $" << fixed << setprecision(2) << acct.lastWithdrawal << endl;
	out << "Last Deposit: $" << fixed << setprecision(2) << acct.lastDeposit << endl;

	return out;
}

// Overloaded assignment operator for AccountInfo structure.
void BankAccount::operator=(AccountInfo &r)
{
	acctInfo.name = r.name;
	acctInfo.address = r.address;
	acctInfo.city = r.city;
	acctInfo.phoneNumber = r.phoneNumber;
	acctInfo.accountType = r.accountType;
	acctInfo.creationDate = r.creationDate;
	acctInfo.balance = r.balance;
	acctInfo.lastWithdrawal = r.lastWithdrawal;
	acctInfo.lastDeposit = r.lastDeposit;
}