#ifndef BOX_CART_H
#define BOX_CART_H


#include <string.h>
#include <stdlib.h>

#define CART_PAYDATE_SIZE 15
#define CART_EMAIL_SIZE 100


typedef struct box_cart box_cart;

extern box_cart *box_cart_fill(int id, char* date, char* email);
extern void box_destroy_cart(box_cart *cart);

extern int box_cart_id(box_cart* cart, int value);
extern char* box_cart_payDate(box_cart* cart, char* value);
extern char* box_cart_email(box_cart* cart, char* value);


#endif