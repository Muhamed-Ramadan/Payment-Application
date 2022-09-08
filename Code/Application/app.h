#ifndef APP_H_
#define APP_H_

#include "../Terminal/terminal.h"
#include "../Card/card.h"
#include "../Server/server.h"
#include <stdio.h>


EN_cardError_t APP_CARD(ST_cardData_t* cardData_P);
EN_terminalError_t APP_TERMINAL(ST_cardData_t* cardData_P, ST_terminalData_t* termData_P);
EN_serverError_t APP_SERVER(ST_transaction_t* transData_P);
#endif //APP_H_