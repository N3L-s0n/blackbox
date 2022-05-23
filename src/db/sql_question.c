#include "sql_question.h"

extern int sql_save_question(MYSQL *connection, box_question* question){
    if(question == NULL) return 1;
    
    int res = SQL_NO_ERROR;
    
    char* query = NULL;


    asprintf(&query, "INSERT INTO Question VALUES('%s','%s','%s','%s')",
        box_question_email(question,NULL),
        box_question_date(question,NULL),
        box_question_subject(question,NULL),
        box_question_description(question, NULL)
        );

    if (mysql_query(connection, query)) res = handle_sql_error(connection);
    
    free(query);
    
    return res;

}