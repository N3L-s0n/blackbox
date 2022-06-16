#ifndef SQL_QUESTION_H
#define SQL_QUESTION_H

#include "sql_connection.h"
#include "../domain/box_question.h"

extern int sql_save_question(MYSQL *connection, box_question* question);

#endif

