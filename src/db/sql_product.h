#ifndef SQL_PRODUCT_H
#define SQL_PRODUCT_H
#include <stdint.h>

#include "sql_connection.h"
#include "../domain/box_product.h"

extern box_product  *sql_get_product(MYSQL *connection, int id);
extern box_products *sql_get_products(MYSQL *connection);

extern box_products *sql_get_products_filter(MYSQL *connection, char *string);
extern box_products *sql_get_products_by_cart_id(MYSQL *connection, int cartId);

extern int sql_get_products_count(MYSQL *connection);
extern int sql_save_product(MYSQL *connection, box_product *product);
extern int sql_get_products_in_cart_count(MYSQL *connection, int cartId);

#endif
