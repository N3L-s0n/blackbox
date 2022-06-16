#include "sql_cart.h"

extern int sql_new_cart(MYSQL *connection, box_cart* cart){
    if(cart == NULL) return 1;
    
    int res = SQL_NO_ERROR;
    
    char* query = NULL;

    asprintf(&query, "INSERT INTO Cart VALUES('%d','%s','%s', '%d')",
        box_cart_id(cart,-1),
        box_cart_payDate(cart,NULL),
        box_cart_email(cart,NULL),
        box_cart_amount(cart, -1)
    );

    if (mysql_query(connection, query)) res = handle_sql_error(connection);
    
    free(query);
    
    return res;
}

extern int sql_cart_add_product(MYSQL* connection, box_cart *cart, box_product *product) {
 
    int res = SQL_NO_ERROR;
    
    char* query = NULL;

    asprintf(&query, "INSERT INTO ProductIsINCart VALUES('%d','%d')",
            box_product_id(product),
            box_cart_id(cart, -1)
    );

    if (mysql_query(connection, query)) res = handle_sql_error(connection);
    
    free(query);
    
    return res;
}

extern int sql_cart_remove_product(MYSQL *connection, box_cart *cart, box_product *product) {

    int res = SQL_NO_ERROR;
    
    char* query = NULL;

    asprintf(&query, "DELETE FROM ProductIsINCart WHERE ProductId='%d' AND CartId='%d'",
            box_product_id(product),
            box_cart_id(cart, -1)
    );

    if (mysql_query(connection, query)) res = handle_sql_error(connection);
    
    free(query);
    
    return res;
}

extern int sql_cart_set_amount(MYSQL *connection, box_cart *cart) {
    
    int res = SQL_NO_ERROR;
    
    char* query = NULL;

    asprintf(&query, "UPDATE Cart SET Amount='%d' WHERE PayDate='-1' AND Id='%d'", box_cart_amount(cart, -1), box_cart_id(cart, -1));

    if (mysql_query(connection, query)) res = handle_sql_error(connection);
    
    free(query);
    
    return res;

}

extern int sql_cart_set_PayDate(MYSQL *connection, box_cart *cart) {
    
    int res = SQL_NO_ERROR;
    
    char* query = NULL;

    char date[15] = {0};
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);
    strftime(date, 15, "%Y/%m/%d", ptm);

    asprintf(&query, "UPDATE Cart SET PayDate='%s', Amount='%d' WHERE PayDate='-1' AND Id='%d'", date, box_cart_amount(cart, -1), box_cart_id(cart, -1));

    if (mysql_query(connection, query)) res = handle_sql_error(connection);
    
    free(query);
    
    return res;
}

extern box_cart *sql_get_cart(MYSQL* connection, box_user *user){
    
    MYSQL_RES *res = NULL;
    MYSQL_ROW  row;

    char *query = NULL;
    box_cart *cart;

    asprintf(&query, "SELECT Cart.Id, Cart.PayDate, Cart.UserEmail, Cart.Amount FROM Cart INNER JOIN User ON Cart.UserEmail=User.Email AND User.Token='%s' AND Cart.PayDate='-1'", box_user_get_token(user));

    if (mysql_query(connection, query)) handle_sql_error(connection);
    
    if ((res = mysql_store_result(connection)) == NULL) handle_sql_error(connection);

    if ((row = mysql_fetch_row(res)) != NULL) {
        cart = box_cart_fill(atoi(row[0]), row[1], row[2], atoi(row[3]));
    }

    mysql_free_result(res);
    free(query);
    
    return cart;
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
        
        if (row[0] == NULL) id = 0;
        else id = atoi(row[0]); 
    }

    mysql_free_result(res);
    free(query);
    
    return id;
}



extern int sql_user_has_cart(MYSQL* connection, box_user *user){
    MYSQL_RES *res = NULL;
    MYSQL_ROW  row;

    char *query = NULL;
    int hasCart = 1;

    asprintf(&query, "SELECT COUNT(*) FROM Cart WHERE UserEmail='%s' AND PayDate='-1'", box_user_get_email(user));

    if (mysql_query(connection, query)) handle_sql_error(connection);
    
    if ((res = mysql_store_result(connection)) == NULL) handle_sql_error(connection);

    if ((row = mysql_fetch_row(res)) != NULL) {
        if(atoi(row[0]) == 0)  hasCart = 0;
    }

    mysql_free_result(res);
    free(query);
    
    return hasCart;

}

