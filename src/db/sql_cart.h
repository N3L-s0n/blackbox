#ifndef SQL_CART_H
#define SQL_CART_H

#include <time.h>
#include "sql_connection.h"
#include "../domain/box_cart.h"

extern int sql_new_cart(MYSQL *connection, box_cart* cart);

extern int sql_set_PayDate(MYSQL *connection, int cartId);

extern int sql_get_cart_id(MYSQL* connection, char* token);

extern int sql_max_id(MYSQL* connection);


#endif