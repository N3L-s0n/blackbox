#define _GNU_SOURCE

#include "../http/box_http.h"
#include "../db/sql_connection.h"
#include "../db/sql_product.h"

#include <stdio.h>

static void set_products(box_http *http, MYSQL *connection);

int main(int argc, char **argv, char **env) {

    box_http *http = box_new_http("../html/products.html", env);
    MYSQL *connection = init_sql_connection();

    box_http_content(http, 2 , TEXT_HTML, CHARSET_UTF_8);
    
    box_set_class_variables(http, "subheader", "subtitle=Check our products.", 0);

    set_products(http, connection);

    close_sql_connection(connection);

    box_send_headers(http);
    box_send_html(http);

    box_destroy_http(http);
}

static void set_products(box_http *http, MYSQL *connection) {

    box_products *products = sql_get_products(connection);
    box_product  *product  = NULL;

    int i = 0;

    int size = box_get_product_array_size(products);

    box_replicate_class(http, "card", 0, size);

    while((product = box_get_product_from_array(products, i)) != NULL) {

        char *name = box_product_name(product, NULL);
        int  price = box_product_price(product, -1);
        int     id = box_product_id(product);

        char *variables = NULL;
        asprintf(&variables, "product-name=%s&product-price=$%d&product-id=%d", name, price, id);

        box_set_class_variables(http, "card", variables, i++);
        free(variables);
    }

    box_destroy_products(products);
}
