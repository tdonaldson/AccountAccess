#include "login.h"

int main()
{
	LogIn li;
	li.loadAccounts();
	li.mainMenu();

	return 0;
}