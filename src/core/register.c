#include "stdlib.h"
#include "stdio.h"
#include "../http/box_http.h"
#include "../db/data.h"
#include "../db/sql_connection.h"


int main(int argc, char **argv, char **env){

    box_http *http = box_new_http("../html/register.html", env);

    box_http_content(http,2, TEXT_HTML,CHARSET_UTF_8);

    box_set_class_variables(http, "subheader", "subtitle=Register new user.", 0);
    
    if (box_http_has_post(http)==1){
        char * email = box_post_param(http,"email");
        char * pass = box_post_param(http,"password");
        char * confpass = box_post_param(http,"confPass");
        char * name = box_post_param(http,"fullname");
        char * phone = box_post_param(http,"phoneNumber");
        char * address = box_post_param(http,"address");
        
        if (box_same_string(pass,confpass) == 0 ){ //confirm password 
            MYSQL *connection = init_sql_connection(); 
            box_user * user =  box_user_fill(email,name,"","",pass,address,phone,NULL, NULL);
            if(sql_create_user(connection,user)==0){
                box_http_redirect(http,"login.cgi");
            }
            close_sql_connection(connection);
        }   
    }
    box_send_headers(http);

    box_send_html(http);
    
    box_destroy_http(http);
    
    return 0; 
}

