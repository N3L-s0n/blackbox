#include "stdlib.h"
#include "stdio.h"
#include "../http/box_http.h"
#include "../db/data.h"
#include "../db/sql_connection.h"


int main(int argc, char **argv, char **env){

    box_http *http = box_new_http("../html/login.html", env);

    box_http_content(http,2, TEXT_HTML,CHARSET_UTF_8);
    box_send_headers(http);

    if (box_http_has_post(http)==1){
        MYSQL *connection = init_sql_connection();
        char * email = box_post_param(http, "email");    
        char * password = box_post_param(http, "password");
        char* log = sql_log_user(connection,email,password);
        //comments
        //printf("%s %s", email, password);
        printf("%s", log );
        if (log!=NULL){ 
            //printf("recibe post");
            // credenciales correctas 
            box_http_setCookie(http,log);
            //free(log);
            box_http_redirect(http,"index.cgi");
            // cambio header set cookie
        }//else sql_log_user == 0 significa contrasena incorrecta o usuario no existente
        

        close_sql_connection(connection);
    }
    //box_http_send(http);
    box_send_html(http);

    box_destroy_http(http); 
    return 0;
}