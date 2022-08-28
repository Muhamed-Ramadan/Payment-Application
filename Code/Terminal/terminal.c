#include <time.h>
#include <stdio.h>
#include<string.h>


#include"terminal.h"



EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) // today's date from windows
{
	EN_terminalError_t terminalState = OK_TERMINAL;
    time_t t;
    struct tm tmp;
    char MY_TIME[11];
    time(&t); //read number of seconds since January 1, 1970
	

    localtime_s(&tmp,&t);//convert sconds to days,months and years. 

    // using strftime to display time in required format.
    strftime(MY_TIME, sizeof(MY_TIME), "%d/%m/%Y", &tmp );


    strcpy_s(termData->transactionDate, 11, MY_TIME);
    return terminalState;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)  // check if the card is expired or not
{
	EN_cardError_t Error = OK_TERMINAL;
	char month_compare = 0;
	char year_compare = 0;

	// convert months date of card expiration and months of current date from ascii to integer
	// then calculate the difference between card month and current month  
	month_compare = (((cardData.cardExpirationDate[0]-'0') * 10) + cardData.cardExpirationDate[1]-'0') -
					(((termData.transactionDate[3]-'0') * 10) + termData.transactionDate[4]-'0');
	
	// convert years date of card expiration and year of current date from ascii to integer
	// then calculate the difference card yrear and current year 
	year_compare = (((cardData.cardExpirationDate[3] - '0') * 10) + cardData.cardExpirationDate[4] - '0') -
					(((termData.transactionDate[8] - '0') * 10) + termData.transactionDate[9] - '0');

	// if the difference < 0 that means the card is expired
	if (year_compare < 0 || month_compare < 0) {
		Error = EXPIRED_CARD;
	}else{}

	return Error;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)  // checking if the pan number format is correct
{
	EN_terminalError_t Error = OK_TERMINAL;
	uint8_t cardPanLen = (uint8_t)strlen(cardData->primaryAccountNumber);
	uint32_t sum = 0;
	uint8_t digit = 0;
	uint8_t checkSum = cardData->primaryAccountNumber[cardPanLen - 1] - '0'; // converting from ascii to integer
	for(int8_t i = cardPanLen-2; i >=0; i--)
	{
		//printf("i = %d,(cardPanLen-2)-i = %d\n",i,(cardPanLen-2)-i);
		if(((cardPanLen-2)-i)%2==0)
		{
			//printf("%c\n", cardData->primaryAccountNumber[i]);
			digit = (cardData->primaryAccountNumber[i] - '0') * 2;
			digit = digit % 10 + digit / 10;
			sum += digit;
		}
		else 
		{
			sum += (cardData->primaryAccountNumber[i] - '0');
		}
		  
		
	}
	if ( (10 - (sum%10)) != checkSum )
	{
		Error = INVALID_CARD;
	}
	return Error;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_cardError_t Error = OK_TERMINAL;
	float transAmount;
	printf("please enter Transaction Amount [max:%.2f $]:",termData->maxTransAmount);
	scanf_s("%f", &transAmount);
	  scanf_s("%*[^\n]"); scanf_s("%*c");//clear upto newline
	if (transAmount > 0) {
		termData->transAmount = transAmount;
	}
	else
	{
		Error = INVALID_AMOUNT;
	}
	return Error;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_cardError_t Error = OK_TERMINAL;
	if ((termData->transAmount) > (termData->maxTransAmount)) {
		Error = EXCEED_MAX_AMOUNT;
	}
	else {}
	return Error;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)  // set the maximum transaction amount can be done per time
{
	 EN_terminalError_t Error = OK_TERMINAL;
	 float transAmount;
    printf("Max amount must be > 0\n");
    printf("Enter Max transaction amount allowed: ");
    scanf_s("%f", &transAmount);
    scanf_s("%*[^\n]"); scanf_s("%*c");//clear upto newline
    if (transAmount <= 0.0)
    {
        Error = INVALID_MAX_AMOUNT;
    }
	else
	{
		termData->maxTransAmount = transAmount;
	}
    return Error;
}

