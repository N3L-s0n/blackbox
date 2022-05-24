#include "../http/box_http.h"
#include "../domain/box_credit_card.h"
#include "../db/sql_credit_card.h"
#include "../db/sql_connection.h"

int main(int argc, char **argv, char **env)
{

    box_http *http = box_new_http("../html/cart.html", env);

    box_http_content(http, 2, TEXT_HTML, CHARSET_UTF_8);

    box_set_class_variables(http, "subheader", "subtitle=Cart.", 0);

    box_send_headers(http);

    if (box_http_has_post(http) == 1)
    {    
        int id = 1;
        char* number;
        char* date;
        int csv;
        char* owner;
        
        if((number = box_post_param(http,"number")) != NULL 
        && (date = box_post_param(http,"expireDate")) != NULL 
        && (owner = box_post_param(http,"owner")) != NULL
        &&(csv = atoi(box_post_param(http,"csv"))) > 99){
            MYSQL *connection = init_sql_connection();
            box_credit_card* card = box_credit_card_fill(id,number,date,csv,owner);
            sql_save_credit_card(connection,card);
            
            close_sql_connection(connection);
            box_destroy_credit_card(card);
            free(number);
            free(date);
            free(owner);
        }
    }
    
    box_http_send(http);
    
    box_destroy_http(http);

    return 0;
}