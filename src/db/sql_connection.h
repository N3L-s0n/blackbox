#ifndef SQL_CONNECTION_H
#define SQL_CONNECTION_H

#define _GNU_SOURCE

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define SQL_DUPLICATE_ENTRY 1062
#define SQL_NO_ERROR        0

extern int handle_sql_error(MYSQL *conn);

extern MYSQL *init_sql_connection(void);
extern void  close_sql_connection(MYSQL *connection);

/* USER DATA */
#include "sql_user.h"

/* PRODUCT DATA */
#include "sql_product.h"

#endif
