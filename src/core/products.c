#define _GNU_SOURCE

#include "../http/box_http.h"
#include "../db/sql_connection.h"
#include "../db/sql_product.h"
#include "../db/sql_user.h"
#include "../db/sql_cart.h"

#include <stdio.h>

static int handle_cart_product(box_http *http, MYSQL *connection);
static void set_products(box_http *http, MYSQL *connection);
static int filter_products(box_http *http, MYSQL *connection);

int main(int argc, char **argv, char **env) {

    box_http *http = box_new_http("../html/products.html", env);
    MYSQL *connection = init_sql_connection();

    box_http_content(http, 2 , TEXT_HTML, CHARSET_UTF_8);
    box_send_headers(http);
    
    if ( box_get_token(http)) handle_cart_product(http, connection);
    if ( filter_products(http, connection) == 0) set_products(http, connection);

    close_sql_connection(connection);
    
    box_set_class_variables(http, "subheader", "subtitle=Check our products.", 0);

    box_send_html(http);
    box_destroy_http(http);

    return 0;
}

static int handle_cart_product(box_http *http, MYSQL *connection) {

    char *id = box_query_param(http, "product-id");

    if (id == NULL || box_check_regex_match(id, NUMERIC) != 0) return 1;

    box_product *product = sql_get_product(connection, atoi(id));

    if (product == NULL) return 1;

    box_user *user = sql_get_user_by_token(connection, box_get_token(http));
    box_cart *cart = sql_get_cart(connection, user);

    int res = sql_cart_add_product(connection, cart, product);

    if (res == SQL_NO_ERROR) 
        box_set_class_variables(http, "subheader", "subtitle=Product added.", 0);
    else
        box_set_class_variables(http, "subheader", "subtitle=Product already added.", 0);

    box_destroy_product(product);
    box_destroy_user(user);
    box_destroy_cart(cart);
}

static int filter_products(box_http *http, MYSQL *connection) {

    char *string = box_query_param(http, "search");

    if (string != NULL) {

        if ( box_check_regex_match(string, ALPHA_NUMERIC) != 0 ) {

            box_replicate_class(http, "card", 0, 0);
            box_set_class_variables(http, "subheader", "subtitle=Try Harder.", 0);
            return 1;
        }

        box_products *products = sql_get_products_filter(connection, string);
        box_product  *product  = NULL;

        int i = 0;

        int size = box_get_product_array_size(products);

        if (size == 0) {
            char *message = NULL;
            asprintf(&message, "subtitle=No products found by search: %s.", string);
            box_set_class_variables(http, "subheader", message, 0);
            free(message);
        }
        else {
            char *message = NULL;

            if(size == 1) asprintf(&message, "subtitle=Found %d product by search: %s.", size, string);
            else asprintf(&message, "subtitle=Found %d products by search: %s.", size, string);

            box_set_class_variables(http, "subheader", message, 0);
            free(message);
        }

        box_replicate_class(http, "card", 0, size);

        while((product = box_get_product_from_array(products, i)) != NULL) {

            char *name = box_product_name(product, NULL);
            char *desc = box_product_description(product, NULL);
            int  price = box_product_price(product, -1);
            int     id = box_product_id(product);

            char *variables = NULL;
            asprintf(&variables, "product-name=%s&product-description=%s&product-price=$%d&product-id=%d", name, desc, price, id);

            box_set_class_variables(http, "card", variables, i++);
            free(variables);
        }

        box_destroy_products(products);

        free(string);
        return 1;
    }

    return 0;

}

static void set_products(box_http *http, MYSQL *connection) {

    box_products *products = sql_get_products(connection);
    box_product  *product  = NULL;

    int i = 0;

    int size = box_get_product_array_size(products);

    if (size == 0) {
        box_set_class_variables(http, "subheader", "subtitle=No products found.", 0);
    }
    else {
        char *message = NULL;

        if(size == 1) asprintf(&message, "subtitle=Check our product & login to add more.", size);
        else asprintf(&message, "subtitle=Check our %d products.", size);

        box_set_class_variables(http, "subheader", message, 0);
        free(message);
    }

    box_replicate_class(http, "card", 0, size);

    while((product = box_get_product_from_array(products, i)) != NULL) {

        char *name = box_product_name(product, NULL);
        char *desc = box_product_description(product, NULL);
        int  price = box_product_price(product, -1);
        int     id = box_product_id(product);

        char *variables = NULL;
        asprintf(&variables, "product-name=%s&product-description=%s&product-price=$%d&product-id=%d", name, desc, price, id);

        box_set_class_variables(http, "card", variables, i++);
        free(variables);
    }

    box_destroy_products(products);
}
