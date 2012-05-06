#include "login.h"
#include "BankAccount.h"

// Constructor for string variables.
LogIn::LogIn()
{
	user = "";
	pass = "";
	delUser = "";
	userFileName = "usernames.dat";
	passFileName = "passwords.dat";
}

// Destructor if the file is open and if there
// is data still stored in the vectors.
LogIn::~LogIn()
{
	vectorSizeCheck();
	openFileCheck();
}

// Creates the menu.
void LogIn::mainMenu()
{
	cout << "-------------\n";
	cout << "--MAIN MENU--\n";
	cout << "-------------\n";
	cout << "1. New\n";
	cout << "2. Existing\n";
	cout << "3. Delete\n";
	cout << "4. Display\n";
	cout << "9. Quit\n";
	choice = inputValidation("Choice", 1, 4);
	cin.get();
	menuChoices();
}

// Gets, from the user, what user they wish to delete
// from the file.
void LogIn::deleteQuery()
{
	cout << "What is the username to delete? ";
	cin >> delUser;
	cin.get();
}

// Dispalys all the contents of the file.
void LogIn::displayContents()
{
	for (int a = 0; a < username.size(); a++)
	{
		cout << "\nUser " << a+1 << ": ";
		cout << username[a] << endl;
	}

	cout << "\n\n";
}

// Takes care of all the choices the user can
// make with the menu.
void LogIn::menuChoices()
{
	switch(choice)
	{
	case 1:
		createAccount();
		cout << endl;
		mainMenu();
		break;
	case 2:
		getUserInfo();
		cout << endl;
		mainMenu();
		break;
	case 3: 
		deleteQuery();
		deleteAccount();
		break;
	case 4:
		displayContents();
		mainMenu();
		break;
	case 9:
		cout << "You have exitted the program.\n";
		exit(EXIT_SUCCESS);
	}
}

// Is called if either the username or password does 
// not match any in the system.
void LogIn::errorMessage()
{
	cout << "The username/password could not be found in the system.\n";
	cout << "Try again\n";
	system("pause");
	system("cls");			
	getUserInfo();
}

// Allows the creation of a new user account.
void LogIn::createAccount()
{
	cout << "Enter your desired username: ";
	cin >> user;
	cin.get();
	username.push_back(user);


	cout << "Enter your desired password: ";
	cin >> pass;
	cin.get();
	password.push_back(pass);

	saveAccounts();

	BankAccount *bank = new BankAccount(user);
}

// Input validation for the directional menu.
int LogIn::inputValidation(string message, int beg, int end)
{
	int value;
	bool failed;
	do
	{
		cout << message << ": ";
		cin.clear();
		if(cin >> value && ((value >= beg && value <= end) || value == 9))
			failed = false;

		else
		{
			failed = true;		
			cout << "New ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	}while(failed == true);  // If user enters 0, then exit out

	return value;
}

// Gathers the information of an existing 
// account in the database.
void LogIn::getUserInfo()
{
	this->user = " ";
	this->pass = " ";
	bool found = false;
	
	// Check to see if the vectors have been initialized.
	// This is required when the user logs out of their
	// bank account and reverts back to the login in screen.
	if (username.size() <= 0 && !file.fail())
		loadAccounts();

	cout << "Enter your username: ";
	getline(cin, this->user);

	if (findUserName())
	{
		cout << "Enter your password: ";
		getline(cin, this->pass);
		BankAccount *bank;
		do
		{
			if (findPassWord())
			{
				system("cls");

				bank = new BankAccount(user);
				bank->BankAccountMenu();

				found = true;
				delete bank;

				break;
			}

			else
				errorMessage();

		} while (!found);
	}

	else
	{
		errorMessage();
	}
}


// Attemps to find the username of the user.
bool LogIn::findUserName()
{
	bool found = false;
	for (int a = 0; a < username.size(); a++)
	{
		if (username[a] == user)
		{
			pos = a + 1;
			found = true;
		}
	}

	return found;
}

// Attempts to find the password of the user.
bool LogIn::findPassWord()
{
	bool found = false;

	if (password[pos-1] == pass)
		found = true;

	return found;
}

// This function loads the data from the file 
// into the userpass vector.
void LogIn::loadAccounts()
{
	file.open(userFileName, ios::in);

	if (file.fail())
	{
		file.open(userFileName, ios::out);
		file.close();
	}
	if (!file.is_open())
		file.open(userFileName, ios::in);

	string temp = "";
	vectorSizeCheck();

	while (!file.eof())
	{
		file >> temp;
		temp = decrypt(temp);
		username.push_back(temp);
		temp = "";
	}

	file.close();

	file.open(passFileName, ios::in);
	
	if (file.fail())
	{
		file.open(passFileName, ios::out);
		file.close();
	}
	if (!file.is_open())
		file.open(passFileName, ios::in);

	while (!file.eof())
	{
		file >> temp;
		temp = decrypt(temp);
		password.push_back(temp);
		temp = "";
	}

	file.close();
}

// Saves the information to the file.
void LogIn::saveAccounts()
{
	file.open(userFileName, ios::out);
	string temp;

	for (int a = 0; a < username.size(); a++)
	{
		temp = encrypt(username[a]);
		file << temp;
		if (a == username.size()-1)
			break;
		else
			file << endl;
	}

	file.close();

	file.open(passFileName, ios::out);

	for (int a = 0; a < password.size(); a++)
	{
		temp = encrypt(password[a]);
		file << temp;
		if (a == password.size()-1)
			break;
		else
			file << endl;
	}

	file.close();
}

// Delets the user's account from the system. 
// Will also delete the file associated with the account.
void LogIn::deleteAccount()
{
	bool erased = false;

	for (int a = 0; a < username.size(); a++)
	{
		if (username[a] == delUser)
		{
			username.erase(username.begin() + a);
			password.erase(password.begin() + a);
			fileName = delUser + ".dat";
			remove(fileName.c_str());
			erased = true;
		}
	}

	if (erased)
	{
		cout << "Account has been deleted.\n";
		cout << "File has been deleted.\n";
		cout << "Saving records...\n";
		saveAccounts();
		cout << "Reverting to main menu now.\n\n";
	}

	else
	{
		cout << "User was unable to be found in database.\n";
		cout << "Reverting to main menu.\n\n";
	}

	mainMenu();
}

// Checks to see if the vector is occupied.
// This is called at the loading of the data
// files and at destruction of the class object.
void LogIn::vectorSizeCheck()
{
	if (username.size() > 0)
		username.empty();

	if (password.size() > 0)
		password.empty();
}

// Check to see if the file is open.
void LogIn::openFileCheck()
{
	// Closes the file if it is open.
	if (file.is_open())
		file.close();
}

// Encrypt the username and password.
string LogIn::encrypt(string word)
{
	string newWord;
	for (int a = 0; a < word.size(); a++)
		newWord += word[a] + 1;

	return newWord;
}

// Decrypt the username and password.
string LogIn::decrypt(string word)
{
	string newWord;
	for (int a = 0; a < word.size(); a++)
		newWord += word[a] - 1;

	return newWord;
}