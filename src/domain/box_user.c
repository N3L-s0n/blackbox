#include "box_user.h"

#define EMAIL_SIZE 100
#define NAME_SIZE 100
#define PASSWORD_SIZE 150
#define ADDRESS_SIZE 200
#define PHONE_SIZE 20
#define TOKEN_SIZE 200
#define TOKEN_TIME 200

typedef struct box_user {
    
    char email[USER_EMAIL_SIZE + 1];
    char name [USER_NAME_SIZE + 1];
    char last_name [USER_NAME_SIZE + 1];
    char second_last_name [USER_NAME_SIZE + 1];

    unsigned char password[SHA256_DIGEST_LENGTH + 1];
    char address[USER_ADDRESS_SIZE + 1];
    char phone[USER_PHONE_SIZE + 1];
    char token_time[USER_TIME_SIZE + 1];


    box_token *token;

} box_user;

typedef struct box_users {
    
    box_user **users;
    size_t size;
    
} box_users;

extern box_user *box_user_new(void) {
    
    box_user *user = (box_user *)calloc(1, sizeof(box_user));
    user->token = NULL;

    return user;
}

extern box_users *box_users_new(size_t size) {

    if (size <= 0) return NULL;

    box_users* users = (box_users *)calloc(1, sizeof(box_users));
    users->users = (box_user **)calloc(size, sizeof(box_user *));
    users->size = size;
    
    return users;
}

extern box_user *box_user_fill(char *email, char *name, char *last_name, char *second_last_name, unsigned char *password, char *address, char *phone, box_token *token, char * toke_time){

    if (email == NULL) return NULL; // key

    email = box_replace_string(email,"%40","@");
    box_user *user = (box_user *)calloc(1, sizeof(box_user));

    strncpy(user->email, email, USER_EMAIL_SIZE);

    if (name != NULL) strncpy(user->name, name, USER_NAME_SIZE);
    if (last_name != NULL) strncpy(user->last_name, last_name, USER_NAME_SIZE);
    if (second_last_name != NULL) strncpy(user->second_last_name, second_last_name, NAME_SIZE);

    if (password != NULL) { 
        memcpy(user->password, password, USER_PASSWORD_SIZE);
        user->password[USER_PASSWORD_SIZE] = '/0'; 
    }

    if (address != NULL) strncpy(user->address, address, USER_ADDRESS_SIZE);
    if (phone != NULL) strncpy(user->phone, phone, USER_PHONE_SIZE);
    if (token != NULL) user->token = token;
    if (toke_time!=NULL)strncpy(user->token_time, toke_time, USER_TIME_SIZE);

    if(validate_length(name,USER_NAME_SIZE)
    &&validate_length(password,USER_PASSWORD_SIZE)
    &&validate_length(address,USER_ADDRESS_SIZE)
    &&validate_length(phone,USER_PHONE_SIZE)
    &&validate_length(email,USER_EMAIL_SIZE)){
        return user;
    }

    return NULL;
    
}

extern void box_destroy_user(box_user *user){

    if (user->token != NULL) box_destroy_token(user->token);
    if (user != NULL) free(user);
}

extern void box_destroy_users(box_users *users) {
    
    if (users != NULL) {
        for (int i = 0; i < users->size; ++i) {

            box_destroy_user(users->users[i]);
        }

        free(users->users);
        free(users);
    }

}

extern box_user *box_get_user_from_array(box_users *users, unsigned int index) {

    if (users == NULL) return NULL;

    if (index >= 0 && index < users->size) return users->users[index];

    return NULL;
}

extern void box_set_user_from_array(box_users *users, box_user *user, unsigned int index) {

    if (users != NULL && user != NULL && index >= 0 && index < users->size)
        users->users[index] = user;
}

extern int box_get_user_array_size(box_users *users) {
    
    if (users != NULL) return users->size;
}

/* KEY */
extern char *box_user_email(box_user *user, char *value) {


    if (value != NULL) strncpy(user->email, value, USER_EMAIL_SIZE);

    return user->email;
}

extern char *box_user_name(box_user *user, char *value) {

    if (value != NULL) strncpy(user->name, value, USER_NAME_SIZE);

    return user->name;
}
extern char *box_user_last_name(box_user *user, char *value) {

    if (value != NULL) strncpy(user->last_name, value, USER_NAME_SIZE);

    return user->last_name;
}
extern char *box_user_second_last_name(box_user *user, char *value) {

    if (value != NULL) strncpy(user->second_last_name, value, USER_NAME_SIZE);

    return user->second_last_name;
}
extern unsigned char *box_user_password(box_user *user, char *value) {

    if (value != NULL) strncpy(user->password, value, USER_PASSWORD_SIZE);

    return user->password;
}
extern char *box_user_address(box_user *user, char *value) {

    if (value != NULL) strncpy(user->address, value, USER_ADDRESS_SIZE);

    return user->address;
}
extern char *box_user_phone(box_user *user, char *value) {

    if (value != NULL) strncpy(user->phone, value, USER_PHONE_SIZE);

    return user->phone;
}
extern box_token *box_user_token(box_user *user, box_token *token) {

    if (user == NULL) return NULL;
    if (token == NULL) return user->token;

    if (user->token != NULL) box_destroy_token(user->token);
    
    user->token = token;

    return user->token;
}
extern char *box_user_token_time(box_user *user, char *value) {

    if (value != NULL) strncpy(user->token_time, value, USER_TIME_SIZE);

    return user->token_time;
}

/*CLEAR*/
extern void box_clear_token(box_user *user){
    if (user!=NULL){
        if(user->token !=NULL)  memset(user->token,0,USER_TOKEN_SIZE);
        if(user->token_time !=NULL)  memset(user->token_time,0,USER_TIME_SIZE);
    }
}


/* GET */
extern char *box_user_get_email(box_user *user){
    return user->email;
}
extern unsigned char *box_user_get_password(box_user *user){
    return user->password;
}
extern box_token *box_user_get_token(box_user *user){
    return user->token;
}
extern char *box_user_get_phone(box_user *user){
    return user->phone;
}
extern char *box_user_get_address(box_user *user){
    return user->address;
}
extern char *box_user_get_token_time(box_user *user){
    return user->token_time;
}
