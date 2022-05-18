#ifndef DATA_H
#define DATA_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/box_regex.h"

//g++ data.c ../utils/box_regex.c -o test `mysql_config --cflags --libs`


MYSQL *connection;

typedef struct user;
typedef struct cart;
typedef struct product;
typedef struct questions;
typedef struct productIsINCart;

extern void innit();
extern void finish_with_error (MYSQL *conn);
extern struct product* getAllProducts(); 
extern int getNumberOfProducts();
extern struct product* getProductsFilteredByName(char* word);
extern struct product* getProductsInUserCart(char* email);
extern void createNewUser(char* email, char* name, char* firstLastName, char* secondLastName, char* password, char* address, char* phone, char* token);
extern bool validatePassword(char* email, char* password);
extern void saveQuestion(char* email, char* date, char* subject, char* description);


#endif