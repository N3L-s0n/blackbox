#ifndef SQL_CART_H
#define SQL_CART_H

#include <time.h>
#include "sql_connection.h"
#include "../domain/box_cart.h"
#include "../domain/box_user.h"
#include "../domain/box_product.h"

extern int sql_new_cart(MYSQL *connection, box_cart* cart);

extern int sql_cart_set_PayDate(MYSQL *connection, box_cart *cart);

extern int sql_cart_set_amount(MYSQL *connection, box_cart *cart);

extern box_cart *sql_get_cart(MYSQL* connection, box_user *user);

extern int sql_max_id(MYSQL* connection);

extern int sql_user_has_cart(MYSQL* connection, box_user *user);

extern int sql_cart_add_product(MYSQL* connection, box_cart *cart, box_product *product, int quantity);

extern int sql_cart_remove_product(MYSQL* connection, box_cart *cart, box_product *product);


#endif
