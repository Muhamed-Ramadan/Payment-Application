
#include<stdio.h>
#include<string.h>
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {         //  gets the Card Holder Name
	EN_cardError_t Error = OK_CARD;
	uint8_t temp[30];              // to hold the name entered by the user
	uint8_t temp_length;           // the len of the name entered by the user
	printf("please enter your name(min:20 -max:24):");
	fgets(temp, 29, stdin);       // 29 to detect if the user enter more than 24
	temp_length = strlen(temp);
	if(temp[temp_length - 1]=='\n'){  // checking that the whole buffer is stored in temp[]
		temp[temp_length - 1] = '\0';
		temp_length--;
	}
	else 
	{
		while (getchar() != '\n');     // clearing stdin buffer (rest of entered data that was not read)
	}
	
	
	for(uint8_t i = 0;i < temp_length;i++)        // checking A-Z , a-z , ' ' and '-'
		{
			if( !( (temp[i] >= 'a' && temp[i]<='z') || (temp[i] >= 'A' && temp[i]<='Z') || (temp[i]==' ') || (temp[i]=='-') ) )
			{
				Error = WRONG_NAME;
				break;
			}
		}
	
	
	if (temp_length < 20 || temp_length > 24) {
		Error = WRONG_NAME;
	}
	else {
		strcpy_s(cardData->cardHolderName,25,temp);    // store the correct name
	}
	return Error;
}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) { // gets the card expiration date (numbers only)
	EN_cardError_t Error = OK_CARD;                    // initially the card is ok
	uint8_t temp[10];                                  // to hold expiration date entered by the user 
	uint8_t temp_length;                               // the len of expiration date entered by the user
	printf("please enter the card expiry date(MM/YY):");
	fgets(temp, 9, stdin);
	temp_length = strlen(temp);

	if (temp[temp_length - 1] == '\n') {                 // checking that the whole buffer is stored in temp[]
		temp[temp_length - 1] = '\0';
		temp_length--;
	}
	else {
		while (getchar() != '\n');              // clearing stdin buffer (rest of entered data that was not read)
	}
	// checking the format is correct (xx/xx) and # of chs is 5                        
	// (00/00) is not accepted , (0x/0x) is accepted 
	// checking that all entered chs are numbers
	if ( (temp_length != 5)||(temp[2]!='/') ) {
	
		
		Error = WRONG_EXP_DATE;
	}
	else if (temp[0] != '0' && temp[0] != '1') // month 0-12 so first number is 0 if month<10, 1 if month>9
	{
		Error = WRONG_EXP_DATE;
	}
	else if(temp[0] == '0')
	{
		if(!(temp[1] > '0' && temp[1] <='9' )) 
		Error = WRONG_EXP_DATE;
	}
	else if(temp[0] == '1')
	{
		if(!(temp[1] >= '0' && temp[1] <='2' ))
		Error = WRONG_EXP_DATE;
	}
	
	else if((temp[3]>='0'&&temp[3]<='9') && (temp[4]>='0'&&temp[4]<='9')) 
	{
		Error = WRONG_EXP_DATE;
	}
	
	if(Error == OK_CARD) {
		strcpy_s(cardData->cardExpirationDate, 6, temp);
	}
	return Error;

}

 



EN_cardError_t getCardPAN(ST_cardData_t* cardData) {      //gets the Card Pan (numbers only)
	EN_cardError_t Error = OK_CARD;						  // initially the card is ok
	uint8_t temp[25];									  // to hold pan entered by the user 
	uint8_t temp_length;								  // the len of pan entered by the user
	printf("please enter card's Primary Account Number(min:16 -max:19):");
	fgets(temp, 24, stdin);
	temp_length = strlen(temp);
	if (temp[temp_length - 1] == '\n') {				  // checking that the whole buffer is stored in temp[]
		temp[temp_length - 1] = '\0';					    
		temp_length--;
	}
	else {
		while (getchar() != '\n');                       // clearing stdin buffer (rest of entered data that was not read)
	}
	if (temp_length < 16 || temp_length > 19) {
		Error = WRONG_PAN;
	}
	else {
		for(uint8_t i = 0;i < temp_length;i++)
		{
			if(temp[i] < '0' || temp[i]>'9')
			{
				Error = WRONG_PAN;
				break;
			}
		}
		
		if(Error==OK_CARD)strcpy_s(cardData->primaryAccountNumber, 20, temp);
	}
	return Error;

}



