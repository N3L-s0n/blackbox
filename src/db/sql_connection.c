#include "sql_connection.h"

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

    box_product *new = box_product_new();
    box_product_name(new, "Blue box");
    box_product_price(new, 50);
    box_product_stock(new, 1);

    sql_save_product(connection, new);
    box_products *products = sql_get_products(connection);

    while((product = box_get_product_from_array(products, i++)) != NULL) {

        printf("==========================\n");

        printf("Id: %d\n", box_product_id(product));
        printf("Name: %s\n", box_product_name(product, NULL));
        printf("Price: %d\n", box_product_price(product, -1));

        printf("==========================\n");
    }

    box_destroy_products(products);
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
