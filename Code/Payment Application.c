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
	while (setMaxAmount(&transData.terminalData) == INVALID_MAX_AMOUNT); // set the max transaction amount 
	//(it loops untill correct value) it is done only one time
	system("cls"); // clear
	do {
		
		do {
			while (APP_CARD(&transData.cardHolderData) != OK_CARD);

			

		} while (APP_TERMINAL(&transData.cardHolderData, &transData.terminalData) != OK_TERMINAL);
	
	} while (APP_SERVER(&transData) != OK_SERVER);

	return 0;
}


/* Testing Codes (commented) */


/*
#include "Terminal/terminal.h"
#include "Card/card.h"
#include "Server/server.h"
#include <stdio.h>
#include<string.h>
*/


/*TESTING getCardHolderName*/
/*
int main()
{
	printf("------------------\n");
	printf("..... TESTING getCardHolderName .....\n");
	printf("------------------\n");
	ST_transaction_t transData;
	EN_cardError_t card_status = OK_CARD; // initial value

	while (1)
	{
		card_status = getCardHolderName(&transData);
		if (card_status == WRONG_NAME)
		{
			printf("Wrong Name, Name must be between 20:24 characters and a-z A-Z ' ' '-' \n");
		}
		else
			printf("accepted \n");
	}
	return 0;

}
*/

/*TESTING getCardExpiryDate*/
/*
int main()
{
	printf("------------------\n");
	printf("..... TESTING getCardExpiryDate .....\n");
	printf("------------------\n");
	ST_transaction_t transData;
	EN_cardError_t card_status = OK_CARD; // initial value

	while (1)
	{
		card_status = getCardExpiryDate(&transData);
		if (card_status == WRONG_EXP_DATE) {
			printf("WRONG Expiration Date \n");
		}
		else
			printf("accepted \n");
	}
	return 0;

}
*/


/*TESTING getCardPAN*/
/*
int main()
{
	printf("------------------\n");
	printf("..... TESTING getCardPAN .....\n");
	printf("------------------\n");
	ST_transaction_t transData;
	EN_cardError_t card_status = OK_CARD; // initial value

	while (1)
	{
		card_status = getCardPAN(&transData);
		if (card_status == WRONG_PAN) {
			printf("WRONG PAN \n");
		}
		else
			printf("accepted \n");
	}
	return 0;

}
*/


/*TESTING isCardExpired*/
/*
int main()
{
	printf("------------------\n");
	printf("..... TESTING isCardExpired .....\n");
	printf("------------------\n");
	ST_transaction_t transData;
	EN_terminalError_t terminal_status = OK_TERMINAL;
	char temp[11];
	while (1)
	{
			printf("please enter the card expiry date (MM/YY):");
			fgets(temp, 9, stdin);
			temp[5] = '\0';
			strcpy_s(&(transData.cardHolderData.cardExpirationDate), 6, temp);
			//printf("\n temp %s %d \n", transData.cardHolderData.cardExpirationDate, transData.cardHolderData.cardExpirationDate[5]);
			printf("...checking the expiration \n");
			printf("please enter the current date (DD/MM/YYYY):");
			fgets(temp, 11, stdin);
			temp[10] = '\0';
			strcpy_s(&(transData.terminalData.transactionDate) , 11, temp);
			terminal_status = isCardExpired(transData.cardHolderData, transData.terminalData);
			//printf("\n temp %s %d \n", transData.terminalData.transactionDate, transData.terminalData.transactionDate[10]);
			if (terminal_status == EXPIRED_CARD)
			{
				printf("Sorry card is Expired\n");
			}
			else
			{
				printf("Cards Date is Valid (is not Expired)\n");
			}
			scanf_s("%*[^\n]"); scanf_s("%*c"); // clearing up to new line
			printf("--end-- \n");

	}
	return 0;
}
*/


/*TESTING isValidCardPAN*/
/*
int main()
{
	printf("------------------\n");
	printf("..... TESTING isValidCardPAN .....\n");
	printf("------------------\n");
	ST_transaction_t transData;
	EN_cardError_t terminal_status = OK_TERMINAL; // initial value
	char temp[25];
	int temp_length;
	while (1)
	{
		printf("please enter card's Primary Account Number(min:16 -max:19):");
		fgets(temp, 24, stdin);
		//clearing buffer
		temp_length = strlen(temp);
		if (temp[temp_length - 1] == '\n') {				  // checking that the whole buffer is stored in temp[]
			temp[temp_length - 1] = '\0';
			temp_length--;
		}
		else  while (getchar() != '\n');                  // clearing stdin buffer (rest of entered data that was not read)
		//end of clearing buffer

		strcpy_s(&transData.cardHolderData.primaryAccountNumber, 20, temp);
		terminal_status = isValidCardPAN(&transData.cardHolderData);
		if (terminal_status == INVALID_CARD) {
			printf("Sorry this card is not valid\n");
		}
		else
			printf("accepted \n");
	}
	return 0;

}
*/

/*Testing isValidAccount*/
/*
int main()
{
	printf("------------------\n");
	printf("..... TESTING isValidAccount .....\n");
	printf("------------------\n");
	ST_transaction_t transData;
	EN_transState_t Error = APPROVED; // initial value
	char temp[25];
	int temp_length;
	while (1)
	{
		printf("please enter card's Primary Account Number(min:16 -max:19) existed in DB:");
		fgets(temp, 24, stdin);
		//clearing buffer
		temp_length = strlen(temp);
		if (temp[temp_length - 1] == '\n') {				  // checking that the whole buffer is stored in temp[]
			temp[temp_length - 1] = '\0';
			temp_length--;
		}
		else  while (getchar() != '\n');                  // clearing stdin buffer (rest of entered data that was not read)
		//end of clearing buffer

		strcpy_s(&transData.cardHolderData.primaryAccountNumber, 20, temp);
		Error = isValidAccount(&transData.cardHolderData);
		if ( Error == DECLINED_STOLEN_CARD)
		{
			Error = DECLINED_STOLEN_CARD;
			printf("Sorry this account is not in database\n");
		}
		else
			printf("this account is existed in database \n");
	}
	return 0;

}
*/

/*TESTING recieveTransactionData*/
/*
int main()
{
	printf("------------------\n");
	printf("..... TESTING recieveTransactionData .....\n");
	printf("------------------\n");
	ST_transaction_t transData;
	EN_transState_t Error = APPROVED; // initial value
	char temp[25];
	int temp_length;
	while (1)
	{
		printf("please enter card's Primary Account Number(min:16 -max:19) existed in DB:");
		fgets(temp, 24, stdin);
		//clearing buffer
		temp_length = strlen(temp);
		if (temp[temp_length - 1] == '\n') {				  // checking that the whole buffer is stored in temp[]
			temp[temp_length - 1] = '\0';
			temp_length--;
		}
		else  while (getchar() != '\n');                  // clearing stdin buffer (rest of entered data that was not read)
		//end of clearing buffer

		strcpy_s(&transData.cardHolderData.primaryAccountNumber, 20, temp);
		Error = recieveTransactionData(&transData.cardHolderData);
		if (Error == DECLINED_STOLEN_CARD)
		{
			Error = DECLINED_STOLEN_CARD;
			printf("Sorry this account is not in database\n");
		}
		else
			printf("this account is existed in database \n");
	}
	return 0;

}
*/