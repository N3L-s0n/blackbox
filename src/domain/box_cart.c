#include "box_cart.h"
#include "box_product.h"

typedef struct box_cart{
    int id;
    char payDate[CART_PAYDATE_SIZE+1];
    char email[CART_EMAIL_SIZE+1];
    int amount;

} box_cart;


extern box_cart *box_cart_fill(int id, char* date, char* email, int amount) {
    box_cart* cart = (box_cart *)calloc(1, sizeof(box_cart));
    
    cart->id = id;

    if(date != NULL) strncpy(cart->payDate, date, CART_PAYDATE_SIZE);
    if(email != NULL) strncpy(cart->email, email, CART_EMAIL_SIZE);

    if(amount >= 0) cart->amount = amount;
    else cart->amount = 0;

    return cart;
}


extern void box_destroy_cart(box_cart *cart){
    if(cart != NULL) free(cart);
}

extern int box_cart_id(box_cart* cart, int value){
    if (value > 0) cart->id = value;
    return cart->id;
}

extern char* box_cart_payDate(box_cart* cart, char* value){
    if (value != NULL) strncpy(cart->payDate, value, CART_PAYDATE_SIZE);

    return cart->payDate;
}

extern char* box_cart_email(box_cart* cart, char* value){
    if (value != NULL) strncpy(cart->email, value, CART_EMAIL_SIZE);

    return cart->email;
}

extern int box_cart_amount(box_cart *cart, int amount) {
    if (amount >= 0) cart->amount = amount;

    return cart->amount;
}
