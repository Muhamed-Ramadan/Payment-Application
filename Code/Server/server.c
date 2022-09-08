#include "server.h"
#include <string.h>
// the accounts database, (balance as a float and pan as a string) per account
ST_accountsDB_t accountsDataBase[255] = { {100.0,"4263982640269299"}, {1000.0,"1806356467113247787"},{500.0,"7189436959119763"},{2500,"4263982640269299"}};
// save transactions details and date
ST_transaction_t transDataBase[255] = { 0 };


static uint8_t Account_Database_Index = 0;     //current user index in accountsDataBase[255]
static uint8_t Transaction_Database_Index = 0; //the index of the next available place in transDataBase[255]



EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	EN_serverError_t Error = DECLINED_STOLEN_CARD;
	for (uint8_t i = 0; i < 255; i++)
	{
		if (strcmp(&cardData->primaryAccountNumber, &accountsDataBase[i].primaryAccountNumber) == 0)
		{
			Error = OK_SERVER;
			Account_Database_Index = i;
			break;
		}
	}
	return Error;
}



EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	EN_serverError_t Error = LOW_BALANCE;
	if (termData->transAmount <= accountsDataBase[Account_Database_Index].balance)
	{
		Error = OK_SERVER;
	}
	return Error;
}





EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	EN_serverError_t Error = OK_SERVER;
	
	if (Transaction_Database_Index == 255) // Transaction_Database_Index
	{
		Error = INTERNAL_SERVER_ERROR;
	}
	else
	{
		transData->transactionSequenceNumber = Transaction_Database_Index;
		//printf("name =  %s\n",transData->cardHolderData.cardHolderName);
		memcpy(&transDataBase[Transaction_Database_Index], transData, sizeof(ST_transaction_t));
		//printf("name =  %s\n", transDataBase[Transaction_Database_Index].cardHolderData.cardHolderName);
		Transaction_Database_Index++;
	}
	return Error;
}





/*LAst point*/
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	/*
	This function will take all transaction data and validate its data.
	It checks the account details and amount availability.
	If the account does not exist return DECLINED_STOLEN_CARD, 
	if the amount is not available will return DECLINED_INSUFFECIENT_FUND, 
	if a transaction can't be saved will return INTERNAL_SERVER_ERROR and will not save the transaction, 
	else returns APPROVED.
	It will update the database with the new balance.
	*/
	//printf("name =  %s\n",transData->cardHolderData.cardHolderName);
	EN_transState_t Error = APPROVED;
	if(isValidAccount(&transData->cardHolderData) == DECLINED_STOLEN_CARD)
	{
		Error = DECLINED_STOLEN_CARD;
	}
	else if(isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
	{
		Error = DECLINED_INSUFFECIENT_FUND;
	}

	if(saveTransaction(transData) == SAVING_FAILED)
	{
		Error = INTERNAL_SERVER_ERROR;
	}
	if(Error == APPROVED)
	{
		accountsDataBase[Account_Database_Index].balance -= transData->terminalData.transAmount;
	}
	return Error;
}











EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	EN_serverError_t Error = OK_SERVER;
	if (transactionSequenceNumber > Transaction_Database_Index || transactionSequenceNumber==255)
	{
		Error = TRANSACTION_NOT_FOUND;
	}
	else
	{
		memcpy(transData, &transDataBase[transactionSequenceNumber ], sizeof(ST_transaction_t));
	}
	return Error;
}