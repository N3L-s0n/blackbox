#ifndef SQL_PRODUCT_H
#define SQL_PRODUCT_H

#include "sql_connection.h"
#include "../domain/box_question.h"

extern int sql_save_question(MYSQL *connection, box_question* question);

#endif

