#include "../http/box_http.h"

int main(int argc, char **argv, char **env){
    
    box_http *http = box_new_http("../html/index.html", env);

    if(box_http_has_post(http)){
        MYSQL *connection= init_sql_connection();
        box_token * token_id = box_get_token(http);
        box_user * user = sql_get_user_by_token(connection,token_id);
        box_clear_token(user);
        sql_save_user(connection,user);
        close_sql_connection(connection);
    }
    box_http_redirect(http,"index.cgi");
    box_destroy_http(http);

    return 0;
}