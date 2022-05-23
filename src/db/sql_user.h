#ifndef SQL_USER_H
#define SQL_USER_H

#include "sql_connection.h"
#include "../domain/box_user.h"

//extern box_user *new_user();
extern box_user  *sql_get_user(MYSQL *connection, char *email);
extern box_users *sql_get_users(MYSQL *connection);

extern int  sql_get_users_count(MYSQL *connection);
extern int  sql_save_user(MYSQL *connection, box_user *user);

#endif
