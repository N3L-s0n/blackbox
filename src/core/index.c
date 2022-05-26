#include "../http/box_http.h"

int main(int argc, char **argv, char **env){
    
    box_http *http = box_new_http("../html/index.html", env);
    /*sls*/

    box_http_content(http, 2, TEXT_HTML, CHARSET_UTF_8);

    box_set_class_variables(http, "subheader", "subtitle=Aiming for secure.", 0);
    
    box_send_headers(http);
    box_send_html(http);

    if(box_http_has_post(http)==1){
        char * logout = box_post_param(http,"logout");
        if (logout == NULL){
            MYSQL *connection= init_sql_connection();
            box_token * token_id = box_get_token(http);
            box_user * user = sql_get_user_by_token(connection,token_id);
            box_clear_token(user);
            sql_save_user(connection,user);
            close_sql_connection(connection);
            box_http_redirect(http,"index.cgi");
        }
    }

    box_destroy_http(http);

    return 0;
}
