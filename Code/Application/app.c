
#include "app.h"




EN_cardError_t APP_CARD(ST_cardData_t* cardData_P)
{
	EN_cardError_t card_status = OK_CARD; // initial value

	card_status = getCardHolderName(cardData_P);
	if (card_status == WRONG_NAME) {
		printf("Wrong Name, Name must be between 20:24 characters and a-z A-Z ' ' '-' \n");
		return card_status;
	}
	printf("================================================= \n");

	card_status = getCardExpiryDate(cardData_P);
	if (card_status == WRONG_EXP_DATE) {
		printf("WRONG Expiration Date \n");
		return card_status;
	}
	printf("================================================= \n");

	card_status = getCardPAN(cardData_P);
	if (card_status == WRONG_PAN) {
		printf("WRONG PAN \n");
		return card_status;
	}
	printf("================================================= \n");
	return card_status;

}


EN_terminalError_t APP_TERMINAL(ST_cardData_t* cardData_P, ST_terminalData_t* termData_P)
{

	EN_terminalError_t terminal_status = OK_TERMINAL;  //initial value

	getTransactionDate(termData_P);      // geting current date from windows

	terminal_status = isCardExpired(*cardData_P, *termData_P);	//ERROrs: OK_TERMINAL, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
	if (terminal_status == EXPIRED_CARD) {
		printf("Sorry card is Expired\n");
		return terminal_status;
	}
	printf("================================================= \n");


	terminal_status = isValidCardPAN(cardData_P);	//ERROrs: OK_TERMINAL, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
	if (terminal_status == INVALID_CARD) {
		printf("Sorry this card is not valid\n");
		return terminal_status;
	}
	printf("================================================= \n");



	terminal_status = getTransactionAmount(termData_P);	//ERROrs: OK_TERMINAL, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
	if (terminal_status == INVALID_AMOUNT) {
		printf("Sorry this amount is not valid\n");
		return terminal_status;
	}
	printf("================================================= \n");


	terminal_status = isBelowMaxAmount(termData_P);	//ERROrs: OK_TERMINAL, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
	if (terminal_status == EXCEED_MAX_AMOUNT) {
		printf("Sorry, You exceeded max amount\n");
		return terminal_status;
	}
	printf("================================================= \n");
	return terminal_status;
}





EN_serverError_t APP_SERVER(ST_transaction_t* transData_P)
{
	EN_serverError_t server_status = OK_SERVER;
	server_status = recieveTransactionData(transData_P);
	if(server_status == DECLINED_STOLEN_CARD)
	{
		printf("This card is stolen\n");
	}
	else if(server_status == DECLINED_INSUFFECIENT_FUND)
	{
		printf("Low Balance\n");
	}
	else if(server_status == SAVING_FAILED)
	{
		printf("Internal server error\n");
	}
	else
	{
		printf("Transaction has been saved\n");
	}
	return server_status;
}