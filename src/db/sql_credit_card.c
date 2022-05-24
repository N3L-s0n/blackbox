#include "sql_credit_card.h"


extern int sql_save_credit_card(MYSQL *connection, box_credit_card *card){
    if(card == NULL) return 1;
    
    int res = SQL_NO_ERROR;
    
    char* query = NULL;

    asprintf(&query, "INSERT INTO CreditCard VALUES('%d','%s','%s','%d','%s')",
        box_credit_card_cart_id(card, -1),
        box_credit_card_number(card,NULL),
        box_credit_card_expiration_date(card,NULL),
        box_credit_card_csv(card,-1),
        box_credit_card_owner(card,NULL)
    );

    if (mysql_query(connection, query)) res = handle_sql_error(connection);
    
    free(query);
    
    return res;

}