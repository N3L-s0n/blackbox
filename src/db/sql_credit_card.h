#ifndef SQL_CREDIT_CARD_H
#define SQL_CREDIT_CARD_H

#include "sql_connection.h"
#include "../domain/box_credit_card.h"

extern int sql_save_credit_card(MYSQL *connection, box_credit_card *card);


#endif