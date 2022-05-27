#include "sql_connection.h"

#include "../domain/box_user.h"
#include "../domain/box_product.h"

extern int handle_sql_error(MYSQL *conn) {

    int errno = mysql_errno(conn);

    if (errno == SQL_DUPLICATE_ENTRY) return errno;
    if (errno == SQL_NO_ERROR) return errno;

    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}


/*
int main (void) {

    MYSQL *connection = init_sql_connection();

    if (connection == NULL) return 0;


    int i = 0;
    box_product *product = NULL;

    box_products *products = sql_get_products(connection);
    box_products *updated = sql_get_products(connection);

    box_product *new = box_product_new();
    box_product_name(new, "Red box");
    box_product_price(new, 50);
    box_product_stock(new, 1);

    box_products_add(updated, new);
    box_products *diff = box_products_diff(products, updated);

    box_destroy_products(products);
    box_destroy_products(updated);

    while((product = box_get_product_from_array(diff, i++)) != NULL) {

        printf("==========================\n");

        printf("Id: %d\n", box_product_id(product));
        printf("Name: %s\n", box_product_name(product, NULL));
        printf("Price: %d\n", box_product_price(product, -1));

        printf("==========================\n");
    }

    box_destroy_products(diff);
    close_sql_connection(connection);

    return 0;
}
*/


extern MYSQL *init_sql_connection(void) {

    MYSQL *connection;

    connection = mysql_init(NULL);

    if (connection == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(connection));
        exit(1);
    }

    if (mysql_real_connect(connection, "localhost", "blackbox", "2uwejs45KSdf8!4$", "blackboxDB", 0, NULL, 0) == NULL)
    {
        handle_sql_error(connection);
    }

    return connection;

}
extern void  close_sql_connection(MYSQL *connection) {
    mysql_close(connection);
}
