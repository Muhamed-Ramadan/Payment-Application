


#include "server.h"
#include<string.h>
// the accounts database, (balance as a float and pan as a string) per account
ST_accountsDB_t accountsDataBase[255] = { {100,"3586766767876"},{500.0,"7189436959119763"} };
// save transactions details and date
ST_transaction_t transDataBase[255] = { 0 };


static uint8_t Account_Database_Index = 0;
static uint8_t Transaction_Database_Index = 0;



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
		accountsDataBase[Account_Database_Index - 1].balance -= transData->terminalData.transAmount;
	}
	return Error;
}



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
	static uint8_t transaSequenceNum = 1;
	if (Transaction_Database_Index == 254)
	{
		Error = INTERNAL_SERVER_ERROR;
	}
	else
	{
		transData->transactionSequenceNumber = transaSequenceNum;

		memcpy(&transDataBase[Transaction_Database_Index], transData, sizeof(ST_transaction_t));
		printf("name =  %s\n", transDataBase[Transaction_Database_Index].cardHolderData.cardHolderName);
		transaSequenceNum++;
		Transaction_Database_Index++;
	}
	return Error;
}


EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	EN_serverError_t Error = OK_SERVER;
	if (transactionSequenceNumber - 1 > Transaction_Database_Index)
	{
		Error = TRANSACTION_NOT_FOUND;
	}
	else
	{
		memcpy(transData, &transDataBase[transactionSequenceNumber - 1], sizeof(ST_transaction_t));
	}
	return Error;
}