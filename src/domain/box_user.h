#ifndef BOX_USER_H
#define BOX_USER_H

#include <string.h>
#include <stdlib.h>
#include "../utils/box_regex.h"

#define USER_EMAIL_SIZE 100
#define USER_NAME_SIZE 100
#define USER_PASSWORD_SIZE 150
#define USER_ADDRESS_SIZE 200
#define USER_PHONE_SIZE 20
#define USER_TOKEN_SIZE 200

typedef struct box_user box_user;
typedef struct box_users box_users;

extern box_user *box_user_new(void);

extern box_users *box_users_new(size_t size);

extern box_user *box_user_fill(char *email, char *name, char *last_name, char *second_last_name, char *password, char *address, char *phone, char *token);

extern void box_destroy_user(box_user *user);

extern void box_destroy_users(box_users *users);

extern box_user *box_get_user_from_array(box_users *users, unsigned int index);
extern int box_get_user_array_size(box_users *users);
extern void box_set_user_from_array(box_users *users, box_user *user, unsigned int index);

/* KEY */
extern char *box_user_email(box_user *user, char *value);
extern char *box_user_name(box_user *user, char *value);
extern char *box_user_last_name(box_user *user, char *value);
extern char *box_user_second_last_name(box_user *user, char *value);
extern char *box_user_password(box_user *user, char *value);
extern char *box_user_address(box_user *user, char *value);
extern char *box_user_phone(box_user *user, char *value);
extern char *box_user_token(box_user *user, char *value);

/* GET */
extern char *box_user_get_email(box_user *user);
extern char *box_user_get_password(box_user *user);
extern char *box_user_get_token(box_user *user);
extern char *box_user_get_phone(box_user *user);
extern char *box_user_get_address(box_user *user);


#endif
