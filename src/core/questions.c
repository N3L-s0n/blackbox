#include "../http/box_http.h"
#include "../domain/box_question.h"
#include "../db/sql_question.h"
#include "../db/sql_connection.h"

int main(int argc, char **argv, char **env)
{

    box_http *http = box_new_http("../html/questions.html", env);

    box_http_content(http, 2, TEXT_HTML, CHARSET_UTF_8);

    box_set_class_variables(http, "subheader", "subtitle=Questions", 0);

    box_send_headers(http);

    if (box_http_has_post(http) == 1)
    {
        char *email;
        char* subject;
        char* description; 
        if((email = box_post_param(http,"email")) != NULL && (subject = box_post_param(http,"subject")) != NULL 
        && (description = box_post_param(http,"description")) != NULL){
            
            
            MYSQL *connection = init_sql_connection();
            box_question* question = box_question_fill(email,subject,description);
            sql_save_question(connection,question);
            
            close_sql_connection(connection);
            box_destroy_question(question);
            free(email);
            free(subject);
            free(description);
        }
    }
    
    box_http_send(http);
    
    box_destroy_http(http);

    return 0;
}