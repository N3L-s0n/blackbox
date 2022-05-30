#include "../http/box_http.h"
#include "../domain/box_question.h"
#include "../db/sql_question.h"
#include "../db/sql_connection.h"

static void handle_quesition_post(box_http *http);


int main(int argc, char **argv, char **env)
{

    box_http *http = box_new_http("../html/questions.html", env);
    box_http_content(http, 2, TEXT_HTML, CHARSET_UTF_8);

    if (box_http_has_post(http) == 1)
    {
        handle_quesition_post(http);
    }
    else{
        box_set_class_variables(http, "subheader", "subtitle=Questions", 0);
    }

    box_send_headers(http);
    box_send_html(http);
    box_destroy_http(http);

    return 0;
}

static void handle_quesition_post(box_http *http){
    char *email;
    char* subject;
    char* description; 
    int res = 0;
    if((email = box_post_param(http,"email")) != NULL && (subject = box_post_param(http,"subject")) != NULL 
    && (description = box_post_param(http,"description")) != NULL){
        MYSQL *connection = init_sql_connection();
        box_question* question = box_question_fill(email,subject,description);
        res = sql_save_question(connection,question);
        
        close_sql_connection(connection);
        box_destroy_question(question);
        free(email);
        free(subject);
        free(description);
    }
    else{
        box_http_redirect(http, "questions.cgi");
        return;
    }

    if (res == SQL_NO_ERROR) box_http_redirect(http, "index.cgi");
    else box_http_redirect(http, "questions.cgi");


}
