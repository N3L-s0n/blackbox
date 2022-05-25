#include "../http/box_http.h"
#include "../db/sql_connection.h"
#include "../db/sql_product.h"

static void handle_product_post(box_http *http);

int main(int argc, char **argv, char **env) {
    
    box_http *http = box_new_http("../html/addProduct.html", env);
    box_http_content(http, 2, TEXT_HTML, CHARSET_UTF_8);


    if (box_http_has_post(http)) handle_product_post(http); 
    else box_set_class_variables(http, "subheader", "subtitle=Add your product.", 0);

    box_send_headers(http);
    box_send_html(http);

    box_destroy_http(http);

    return 0;
}

static void handle_product_post(box_http *http) {

    char *name = box_post_param(http, "name");
    char *description = box_post_param(http, "description");
    char *price = box_post_param(http, "price");

    if (name == NULL || description == NULL || price == NULL) {

        box_http_redirect(http, "addProduct.cgi");
        return;
    }

    if (box_check_regex_match(price, NUMERIC) != 0) {

        box_http_redirect(http, "addProduct.cgi");
        return;
    }

    MYSQL *connection = init_sql_connection();

    box_product *product = box_product_new();

    box_product_name(product, name);
    box_product_description(product, description);
    box_product_price(product, atoi(price));

    int res = sql_save_product(connection, product);

    box_destroy_product(product);
    close_sql_connection(connection);

    if (res == SQL_NO_ERROR) box_http_redirect(http, "products.cgi");
    else box_http_redirect(http, "addProduct.cgi");
}
