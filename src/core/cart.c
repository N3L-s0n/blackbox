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

static void set_cart_products(box_http *http, MYSQL *connection);

static void handle_payment(box_http *http, MYSQL *connection);

int main(int argc, char **argv, char **env)
{
   
    box_http *http = box_new_http("../html/cart.html", env);
    box_http_content(http, 2, TEXT_HTML, CHARSET_UTF_8);

    MYSQL *connection = init_sql_connection();

    if(box_http_logged(http) == USER_LOGGED) {
        
        set_cart_products(http, connection);

        if (box_http_has_post(http) == 1) handle_payment(http, connection);
    }
    else box_set_class_variables(http, "subheader", "subtitle=Not logged.", 0);

    box_set_class_variables(http, "subheader", "subtitle=Cart.", 0);
    

    box_send_headers(http);
    box_send_html(http);

    close_sql_connection(connection);
    box_destroy_http(http);

    return 0;
}

static void set_cart_products(box_http *http, MYSQL *connection)
{
    box_user *user = sql_get_user_by_token(connection, box_get_token(http));
    box_cart *cart = sql_get_cart(connection, user);

    box_products *products = sql_get_products_by_cart_id(connection, cart);
    box_product *product = NULL;

    int i = 0;

    if (box_get_product_array_size(products) > 0) {
        box_replicate_class(http, "productsList", 0, box_get_product_array_size(products));

        char *total = NULL;
        int amount = box_get_products_total(products);

        asprintf(&total, "total=%d USD", amount);
        box_set_class_variables(http, "card", total, 0);

        box_cart_amount(cart, amount);
        sql_cart_set_amount(connection, cart); 

        free(total);
    }
    else {
        box_hide_class(http, "row", 1);
        box_set_class_variables(http, "productsList",  "product-name=-&product-description=-&product-price=-", 0);
        box_set_class_variables(http, "subheader", "subtitle=Your shopping cart has no products.", 0);
    }

    while ((product = box_get_product_from_array(products, i)) != NULL)
    {
        char *variables = NULL;

        asprintf(&variables, "product-name=%s&product-description=%s&product-price=$%d&product-id=%d", 
                    box_product_name(product, NULL),
                    box_product_description(product, NULL),
                    box_product_price(product, -1),
                    box_product_id(product)
                );

        box_set_class_variables(http, "productsList", variables, i++);
        free(variables);
    }

    box_destroy_user(user);
    box_destroy_cart(cart);
    box_destroy_products(products);
}

static void handle_payment(box_http *http, MYSQL *connection)
{
    box_user *user = sql_get_user_by_token(connection, box_get_token(http));
    box_cart *cart = sql_get_cart(connection, user);

    char *number = box_post_param(http, "cardNumber");
    char *csv = box_post_param(http, "csv");
    char *owner = box_post_param(http, "owner");

    char *year = box_post_param(http, "expireYear");
    char *month = box_post_param(http, "expireMonth");
    char *date;

    int res = -1;

    int products_count = sql_get_products_in_cart_count(connection, cart);

    if (number!=NULL && csv!=NULL && owner!=NULL && year!=NULL && month!=NULL && products_count>0)
    {
        asprintf(&date, "%s/%s", month, year);

        if (validateCard(number, atoi(month), atoi(year), csv) == 1) {

            box_credit_card *card = box_credit_card_fill(box_cart_id(cart, -1), number, date, csv, owner);
            res = sql_save_credit_card(connection, card);
            box_destroy_credit_card(card);

            if (res == SQL_NO_ERROR)
            {
                sql_cart_set_PayDate(connection, cart);
                box_cart *new_cart = box_cart_fill(sql_max_id(connection) + 1, "-1", box_user_email(user, NULL), 0);
                sql_new_cart(connection, new_cart);
                box_destroy_cart(new_cart);

                box_http_redirect(http, "index.cgi");
            }
            else 
                box_set_class_variables(http, "subheader", "subtitle=Something went wrong.", 0);
        }
        else box_set_class_variables(http, "subheader", "subtitle=Invalid card, try again.", 0);

        free(number);
        free(csv);
        free(owner);

        free(year);
        free(month);
        free(date);
    }

    box_destroy_user(user);
    box_destroy_cart(cart);
}
