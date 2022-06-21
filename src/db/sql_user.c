#include "sql_user.h"

extern box_user  *sql_get_user(MYSQL *connection, char *email) {

    MYSQL_RES *res = NULL;
    MYSQL_ROW  row;

    char *query = NULL;
    box_user *user = NULL;
    email = box_replace_string(email,"%40","@"); //solve %40 in input instead of @
    asprintf(&query, "SELECT * from User where Email = '%s'", email);

    if (mysql_query(connection, query)) handle_sql_error(connection);
    
    if ((res = mysql_store_result(connection)) == NULL) handle_sql_error(connection);

    if ((row = mysql_fetch_row(res)) != NULL) {
        user = box_user_fill(row[0], row[1], row[2], row[3], row[4], row[5], row[6], box_new_token(row[7]),row[8]);
    }

    mysql_free_result(res);
    free(query);

    return user;
}

extern box_user *sql_get_user_by_token(MYSQL *connection, box_token *token) {

    if (connection == NULL || token == NULL || box_get_token_value(token) == NULL) return NULL;


    MYSQL_RES *res = NULL;
    MYSQL_ROW  row;

    char *query = NULL;
    box_user *user = NULL;

    asprintf(&query, "SELECT * from User where Token = '%s'", box_get_token_value(token));

    if (mysql_query(connection, query)) handle_sql_error(connection);
    
    if ((res = mysql_store_result(connection)) == NULL) handle_sql_error(connection);

    if ((row = mysql_fetch_row(res)) != NULL) {
        user = box_user_fill(row[0], row[1], row[2], row[3], row[4], row[5], row[6], box_new_token(row[7]), row[8]);
    }

    mysql_free_result(res);
    free(query);
    

    return user;
}

extern box_users *sql_get_users(MYSQL *connection) {

    MYSQL_RES *res = NULL;
    MYSQL_ROW  row;

    uint64_t rows = 0;

    char *query = NULL;

    asprintf(&query, "SELECT * from User");

    if (mysql_query(connection, query)) handle_sql_error(connection);
    
    if ((res = mysql_store_result(connection)) == NULL) handle_sql_error(connection);

    rows = mysql_num_rows(res);

    box_users* users = box_users_new(rows);
    if (users != NULL) {
        int i = 0;

        while ((row = mysql_fetch_row(res)) != NULL) {
            box_set_user_from_array(users, box_user_fill(row[0], row[1], row[2], row[3], row[4], row[5], row[6], box_new_token(row[7]),row[8]), i++);
        }
    }

    mysql_free_result(res);
    free(query);

    return users;
}
extern int   sql_get_users_count(MYSQL *connection) {

    MYSQL_RES *res = NULL;
    MYSQL_ROW  row;

    char *query = NULL;
    int count = 0;

    asprintf(&query, "SELECT COUNT(*) FROM User");

    if (mysql_query(connection, query)) handle_sql_error(connection);
    
    if ((res = mysql_store_result(connection)) == NULL) handle_sql_error(connection);

    if ((row = mysql_fetch_row(res)) != NULL) {

        count = atoi(row[0]); 
    }

    mysql_free_result(res);
    free(query);
    
    return count;
}

extern int  sql_save_user(MYSQL *connection, box_user *user) {
    if (user==NULL)return 1; 
    MYSQL_ROW row; 
    char * query= NULL;
    int res = SQL_NO_ERROR;

    char * hex = box_hex(box_user_password(user, NULL), USER_PASSWORD_SIZE);

    asprintf(&query, "UPDATE User SET Name='%s',FirstLastName='%s',SecondLastName='%s',Password=UNHEX('%s'),Address='%s',Phone='%s',Token='%s',TokenTime='%s' WHERE Email='%s'", 
            box_user_name(user, NULL),
            box_user_last_name(user, NULL),
            box_user_second_last_name(user, NULL),
            hex,
            box_user_address(user, NULL),
            box_user_phone(user, NULL),
            box_user_token(user, NULL),
            box_user_token_time(user,NULL),
            box_user_email(user,NULL)
            );


    free(hex);

    if (mysql_query(connection, query)) res = handle_sql_error(connection);
    
    free(query);
    
    return res;
    
}
extern int  sql_create_user(MYSQL *connection, box_user *user) {

    if (user == NULL) return 1;

    MYSQL_ROW  row;
    int res = SQL_NO_ERROR;

    char *query = NULL;

    char * hex = box_hex(box_user_password(user, NULL), USER_PASSWORD_SIZE);

    asprintf(&query, "INSERT INTO User VALUES('%s', '%s', '%s', '%s', UNHEX('%s'), '%s', '%s','%s','%s')", 
            box_user_email(user, NULL),
            box_user_name(user, NULL),
            box_user_last_name(user, NULL),
            box_user_second_last_name(user, NULL),
            hex,
            box_user_address(user, NULL),
            box_user_phone(user, NULL),
            "",
            ""
            );

    free(hex);

    if (mysql_query(connection, query)) res = handle_sql_error(connection);
    
    free(query);
    
    return res;
}

extern box_user *sql_log_user(MYSQL *connection, char *email, char *password) {

    box_user *user = sql_get_user(connection,email);

    if (user == NULL) return NULL;

    unsigned char   *digest = box_sha256(password);

    if (digest != NULL && memcmp(digest, box_user_get_password(user), SHA256_DIGEST_LENGTH) == 0) {

            box_user_token_time(user,box_get_timestamp());
            box_user_token(user, box_craft_token()); // le asigno un token 
                                                             
            if (sql_save_user(connection,user) != SQL_NO_ERROR) {
    
                box_destroy_user(user);
                user = NULL;
            }

            free(digest);
    }
    else {
        box_destroy_user(user);
        user = NULL;
    }

    return user;
}

