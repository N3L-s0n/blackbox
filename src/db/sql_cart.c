#include "sql_cart.h"

extern int sql_new_cart(MYSQL *connection, box_cart* cart){
    if(cart == NULL) return 1;
    
    int res = SQL_NO_ERROR;
    
    char* query = NULL;

    asprintf(&query, "INSERT INTO Cart VALUES('%d','%s','%s')",
        box_cart_id(cart,-1),
        box_cart_payDate(cart,NULL),
        box_cart_email(cart,NULL)
    );

    if (mysql_query(connection, query)) res = handle_sql_error(connection);
    
    free(query);
    
    return res;
}

extern int sql_set_PayDate(MYSQL *connection, int cartId){
    
    int res = SQL_NO_ERROR;
    
    char* query = NULL;

    char date[15] = {0};
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);
    strftime(date, 15, "%Y-%m-%d", ptm);

    asprintf(&query, "UPDATE Cart SET PayDate=%s WHERE PayDate=-1 AND Id=%d", date, cartId);

    if (mysql_query(connection, query)) res = handle_sql_error(connection);
    
    free(query);
    
    return res;
}

extern int sql_get_cart_id(MYSQL* connection, char* token){
    
    MYSQL_RES *res = NULL;
    MYSQL_ROW  row;

    char *query = NULL;
    int id = 0;

    asprintf(&query, "SELECT Cart.Id FROM Cart INNER JOIN User ON Cart.UserEmail=User.Email AND User.Token=%s AND Cart.PayDate=-1",token);

    if (mysql_query(connection, query)) handle_sql_error(connection);
    
    if ((res = mysql_store_result(connection)) == NULL) handle_sql_error(connection);

    if ((row = mysql_fetch_row(res)) != NULL) {
        id = atoi(row[0]); 
    }

    mysql_free_result(res);
    free(query);
    
    return id;
}

extern int sql_max_id(MYSQL* connection){
        MYSQL_RES *res = NULL;
    MYSQL_ROW  row;

    char *query = NULL;
    int id = 0;

    asprintf(&query, "SELECT MAX(Id) FROM Cart");

    if (mysql_query(connection, query)) handle_sql_error(connection);
    
    if ((res = mysql_store_result(connection)) == NULL) handle_sql_error(connection);

    if ((row = mysql_fetch_row(res)) != NULL) {
        id = atoi(row[0]); 
    }

    mysql_free_result(res);
    free(query);
    
    return id;
}

