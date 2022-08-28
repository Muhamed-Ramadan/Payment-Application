// Payment Application.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Application/app.h"

int main()
{
	printf("------------------\n");
	printf("..... Welcom .....\n");
	printf("------------------\n");
	ST_transaction_t transData;
	//transData.cardHolderData == {"", "", "4263982640269299"};
	while (setMaxAmount(&transData.terminalData) == INVALID_MAX_AMOUNT);
	do {
		do {
			while (APP_CARD(&transData.cardHolderData) != OK_CARD);

			system("cls");

		} while (APP_TERMINAL(&transData.cardHolderData, &transData.terminalData) != OK_TERMINAL);
	} while (APP_SERVER(&transData) != OK_SERVER);

	return 0;
}




/*

	ST_cardData_t cardData = {"ramadan","7189436959119763","08/23"};
	ST_cardData_t cardData1 = {"ehab","4263982640269299","08/23"};

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

		printf("Amount Available \n");
	}
	if (saveTransaction(&transData) == OK_SERVER)
	{
		printf("Transaction is saved \n");
	}



	if (recieveTransactionData(&transData) == APPROVED)
	{
		printf("recieveTransaction done\n");
	}
	*/

	// Run program: Ctrl + F5 or Debug > Start Without Debugging menu// Debug program: F5 or Debug > Start Debugging menu

	// Tips for Getting Started: 
	//   1. Use the Solution Explorer window to add/manage files
	//   2. Use the Team Explorer window to connect to source control
	//   3. Use the Output window to see build output and other messages
	//   4. Use the Error List window to view errors
	//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
	//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
