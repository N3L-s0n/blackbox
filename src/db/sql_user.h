#ifndef SQL_USER_H
#define SQL_USER_H

#include "sql_connection.h"
#include "../domain/box_user.h"
#include "../utils/box_regex.h"
#include "../utils/box_client_token.h"


extern box_user  *sql_get_user(MYSQL *connection, char *email);
extern box_user  *sql_get_user_by_token(MYSQL *connection, box_token *token);

extern box_users *sql_get_users(MYSQL *connection);

extern int sql_get_users_count(MYSQL *connection);
extern int sql_create_user(MYSQL *connection, box_user *user);
extern int sql_save_user(MYSQL *conection, box_user *user);

extern box_token *sql_log_user(MYSQL * connection, char *email, char *password);

#endif
