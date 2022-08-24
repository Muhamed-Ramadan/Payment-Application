// Payment Application.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include "./Card/card.h"
#include "./Terminal/terminal.h"
#include "Server/server.h"
int main()
{
	ST_cardData_t cardData = {"ramadan","7189436959119763","08/23"};
	ST_cardData_t cardData1 = {"ehab","7189436959119763","08/23"};

	ST_terminalData_t termData = {5000,5000,"21/08/2022"};
	ST_transaction_t transData = { cardData,termData,0 };
	ST_transaction_t transData1 = { cardData1,termData,0 };

	
	if(isValidAccount(&cardData) == OK_SERVER)
	{
		printf("%s\n", cardData.primaryAccountNumber);
		printf("correct PAN\n");
	}
	if (isAmountAvailable(&termData) == OK_SERVER)
	{
		
		printf("Amount Availabe \n");
	}
	if (saveTransaction(&transData) == OK_SERVER)
	{
		printf("Transaction is saved \n");
	}
	if (getTransaction(1, &transData) == OK_SERVER)
	{
		printf("Transaction is found : %s \n" , transData.cardHolderData.cardHolderName  );
	}
	
	
	if (getTransaction(2, &transData) == OK_SERVER)
	{
		printf("Transaction is found : %s \n" , transData1.cardHolderData.cardHolderName  );
	}
	else
	{
		printf("Transaction not found :  \n");
	}
	
	if (getTransaction(3, &transData) == TRANSACTION_NOT_FOUND)
	{
		printf("Transaction not found\n");
	}

	if (recieveTransactionData(&transData) == APPROVED)
	{
		printf("recieveTransaction done\n");
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
