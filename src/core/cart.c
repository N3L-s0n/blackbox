#include "../http/box_http.h"
#include "../domain/box_credit_card.h"
#include "../db/sql_credit_card.h"
#include "../db/sql_connection.h"
#include "../db/sql_product.h"
#include "../utils/box_card_validation.h"
#include "../db/sql_cart.h"

#include <stdio.h>
#include <stdlib.h>

static void set_cart_products(box_http *http, MYSQL *connection, int cartId);

static void handle_card(box_http *http, MYSQL *connection, int cartId, char* email);

int main(int argc, char **argv, char **env)
{

    box_http *http = box_new_http("../html/cart.html", env);
    MYSQL *connection = init_sql_connection();
    char* token = "123";
    char* email = "x";
    int cartId = sql_get_cart_id(connection,token);

    box_http_content(http, 2, TEXT_HTML, CHARSET_UTF_8);

    box_set_class_variables(http, "subheader", "subtitle=Cart", 0);

    box_send_headers(http);

    if (box_http_has_post(http) == 1)
    {
        handle_card(http, connection, cartId, email);
    }

    set_cart_products(http, connection, cartId);

    box_http_send(http);

    close_sql_connection(connection);
    box_destroy_http(http);

    return 0;
}

static void set_cart_products(box_http *http, MYSQL *connection, int cartId)
{

    box_products *products = sql_get_products_by_cart_id(connection, cartId);
    box_product *product = NULL;

    int i = 0;

    int size = box_get_product_array_size(products);

    if (size > 1)
        box_replicate_class(http, "productsList", 0, size);

    while ((product = box_get_product_from_array(products, i)) != NULL)
    {
        char *name = box_product_name(product, NULL);
        int price = box_product_price(product, -1);
        char *description = box_product_description(product, NULL);

        char *variables = NULL;
        asprintf(&variables, "product-name=%s&product-description=%s&product-price=$%d", name, description, price);

        box_set_class_variables(http, "productsList", variables, i++);
        free(variables);
    }
    /*if(size == 0){
        char *vars = "product-name=x&product-description=x&product-price=$x";
        box_set_class_variables(http, "productsList", vars, i++);
        free(vars);
    }*/

    box_destroy_products(products);
}

static void handle_card(box_http *http, MYSQL *connection, int cartId, char* email)
{
    char *number = NULL;
    int year;
    int month;
    char *date = NULL;
    char *csv = NULL;
    char *owner = NULL;

    if ((number = box_post_param(http, "cardNumber")) != NULL 
    && (owner = box_post_param(http, "owner")) != NULL 
    && (csv = box_post_param(http, "csv")) != NULL)
    {
        month = atoi(box_post_param(http, "expireMonth"));
        year = atoi(box_post_param(http, "expireYear"));

        asprintf(&date, "%d/%d", month, year);

        if(validateCard(number, month, year, csv) == 1){
            box_credit_card *card = box_credit_card_fill(cartId, number, date, csv, owner);
            sql_save_credit_card(connection, card);
            box_destroy_credit_card(card);

            sql_set_PayDate(connection,cartId);
            box_cart* new_cart = box_cart_fill(sql_max_id(connection)+1,"-1",email);
            sql_new_cart(connection,new_cart);
            box_destroy_cart(new_cart);
        }

        free(number);
        free(date);
        free(owner);
    }
}