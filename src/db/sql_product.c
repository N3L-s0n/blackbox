#include "sql_product.h"

/* USER DATA */
extern box_product  *sql_get_product(MYSQL *connection, int id) {

    MYSQL_RES *res = NULL;
    MYSQL_ROW  row;

    char *query = NULL;
    box_product *product = NULL;

    asprintf(&query, "SELECT * from Product where Id = '%d'", id);

    if (mysql_query(connection, query)) handle_sql_error(connection);
    
    if ((res = mysql_store_result(connection)) == NULL) handle_sql_error(connection);

    if ((row = mysql_fetch_row(res)) != NULL) {
        product = box_product_fill(
                atoi(row[0]),
                row[1],
                atoi(row[2]),
                atoi(row[3]),
                row[4],
                row[5]
                );
    }

    mysql_free_result(res);
    free(query);

    return product;
}
extern box_products *sql_get_products(MYSQL *connection) {

    MYSQL_RES *res = NULL;
    MYSQL_ROW  row;

    uint64_t rows = 0;

    char *query = NULL;

    asprintf(&query, "SELECT * from Product");

    if (mysql_query(connection, query)) handle_sql_error(connection);
    
    if ((res = mysql_store_result(connection)) == NULL) handle_sql_error(connection);

    rows = mysql_num_rows(res);

    box_products* products = box_products_new(rows);
    if (products != NULL) {
        int i = 0;

        while ((row = mysql_fetch_row(res)) != NULL) {

            box_set_product_from_array(products, 
                    box_product_fill(
                        atoi(row[0]), 
                        row[1], 
                        atoi(row[2]), 
                        atoi(row[3]), 
                        row[4], 
                        row[5]
                        ), 
                    i++);
        }
    }

    mysql_free_result(res);
    free(query);

    return products;
}
extern int   sql_get_products_count(MYSQL *connection) {

    MYSQL_RES *res = NULL;
    MYSQL_ROW  row;

    char *query = NULL;
    int count = 0;

    asprintf(&query, "SELECT COUNT(*) FROM Product");

    if (mysql_query(connection, query)) handle_sql_error(connection);
    
    if ((res = mysql_store_result(connection)) == NULL) handle_sql_error(connection);

    if ((row = mysql_fetch_row(res)) != NULL) {

        count = atoi(row[0]); 
    }

    mysql_free_result(res);
    free(query);
    
    return count;
}

extern int  sql_save_product(MYSQL *connection, box_product *product) {

    if (product == NULL) return 1;

    MYSQL_ROW  row;
    int res = SQL_NO_ERROR;

    char *query = NULL;

    asprintf(&query, "INSERT INTO Product (Name, Price, Stock, Description, Image) VALUES('%s', '%d', '%d', '%s', '%s')", 
            box_product_name(product, NULL),
            box_product_price(product, -1),
            box_product_stock(product, -1),
            box_product_description(product, NULL),
            box_product_image(product, NULL)
            );

    if (mysql_query(connection, query)) res = handle_sql_error(connection);
    
    free(query);
    
    return res;
}


