#include "../http/box_http.h"
#include "../domain/box_credit_card.h"
#include "../db/sql_credit_card.h"
#include "../db/sql_connection.h"
#include "../db/sql_product.h"
#include "../utils/box_card_validation.h"
#include "../db/sql_cart.h"
#include "../db/sql_user.h"
#include "../http/box_http.h"

#include <stdio.h>
#include <stdlib.h>

static void set_cart_products(box_http *http, MYSQL *connection, int cartId);

static void handle_card(box_http *http, MYSQL *connection, int cartId, char *email);

static void no_products(box_http *http);

int main(int argc, char **argv, char **env)
{
   
    box_http *http = box_new_http("../html/cart.html", env);
    box_http_content(http, 2, TEXT_HTML, CHARSET_UTF_8);

    char* token = NULL;
    char* email = NULL;
    int cartId;

    MYSQL *connection = init_sql_connection();
    box_token* t = box_get_token(http);
    token = box_get_token_value(t);
    if(token!=NULL) {
        email = box_user_email(sql_get_user_by_token(connection,t),NULL);
        cartId = sql_get_cart_id(connection, token);
    }

    if (box_http_has_post(http) == 1 && token!=NULL)
    {
        handle_card(http, connection, cartId, email);
    }
    else
    {
        box_set_class_variables(http, "subheader", "subtitle=Cart", 0);
    }

    if(token!=NULL) set_cart_products(http, connection, cartId);
    else no_products(http);
    

    box_send_headers(http);
    box_send_html(http);
    close_sql_connection(connection);
    box_destroy_http(http);

    return 0;
}

static void no_products(box_http *http){
    box_set_class_variables(http, "productsList", "product-name=-&product-description=-&product-price=-", 0);
}

static void set_cart_products(box_http *http, MYSQL *connection, int cartId)
{
    box_products *products = sql_get_products_by_cart_id(connection, cartId);
    box_product *product = NULL;

    int i = 0;

    int size = box_get_product_array_size(products);

    if (size > 1)
        box_replicate_class(http, "productsList", 0, size);

    if (size == 0)
    {
        no_products(http);
    }

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

    box_destroy_products(products);
}

static void handle_card(box_http *http, MYSQL *connection, int cartId, char *email)
{
    char *number = NULL;
    char *date = NULL;
    char *csv = NULL;
    char *owner = NULL;
    int year;
    int month;
    int res = -1;

    int numberOfProducts = sql_get_products_in_cart_count(connection, cartId);

    if ((number = box_post_param(http, "cardNumber")) != NULL && (owner = box_post_param(http, "owner")) != NULL && (csv = box_post_param(http, "csv")) != NULL && (numberOfProducts > 0))
    {

        month = atoi(box_post_param(http, "expireMonth"));
        year = atoi(box_post_param(http, "expireYear"));

        asprintf(&date, "%d/%d", month, year);

        if(validateCard(number, month, year, csv) == 1){
            box_credit_card *card = box_credit_card_fill(cartId, number, date, csv, owner);
            res = sql_save_credit_card(connection, card);
            box_destroy_credit_card(card);

            if (res == SQL_NO_ERROR)
            {
                sql_set_PayDate(connection, cartId);
                box_cart *new_cart = box_cart_fill(sql_max_id(connection) + 1, "-1", email);
                sql_new_cart(connection, new_cart);
                box_destroy_cart(new_cart);
            }
        }

        free(number);
        free(date);
        free(owner);
    }
    else
    {
        box_http_redirect(http, "cart.cgi");
        return;
    }

    if (res == SQL_NO_ERROR)
        box_http_redirect(http, "index.cgi");
    else
        box_http_redirect(http, "cart.cgi");
}