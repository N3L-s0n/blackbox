#include "box_credit_card.h"


typedef struct box_credit_card{
    int cartID;
    int csv;

    char cardNumber[CREDIT_CARD_NUMBER_SIZE+1];
    char expirationDate[CREDIT_CARD_EXP_DATE_SIZE+1];
    char cardOwner[CREDIT_CARD_OWNER_SIZE+1];
} box_credit_card;



extern box_credit_card *box_credit_card_new(void){
    box_credit_card* card = (box_credit_card *)calloc(1, sizeof(box_credit_card));
    return card;
}


extern box_credit_card *box_credit_card_fill(int id, char* number, char* date, int csv, char* owner){

    box_credit_card* card = (box_credit_card *)calloc(1, sizeof(box_credit_card));
    
    card->cartID = id;
    card->csv = csv;

    if(number != NULL) strncpy(card->cardNumber, number, CREDIT_CARD_NUMBER_SIZE);
    if(date != NULL) strncpy(card->expirationDate, date, CREDIT_CARD_EXP_DATE_SIZE);
    if(owner != NULL) strncpy(card->cardOwner, owner, CREDIT_CARD_OWNER_SIZE);

    return card;
}

extern void box_destroy_credit_card(box_credit_card *card){
    if(card != NULL) free(card);
}

extern int box_credit_card_cart_id(box_credit_card *card, int value){
    return card->cartID;
}

extern char *box_credit_card_number(box_credit_card *card, char *value){
    
    if (value != NULL) strncpy(card->cardNumber, value, CREDIT_CARD_NUMBER_SIZE);

    return card->cardNumber;
}

extern char *box_credit_card_expiration_date(box_credit_card *card, char *value){

    if (value != NULL) strncpy(card->expirationDate, value, CREDIT_CARD_EXP_DATE_SIZE);

    return card->expirationDate;
}

extern int box_credit_card_csv(box_credit_card *card, int value){
    
    if (value > 0) card->csv = value;

    return card->csv;
}

extern char *box_credit_card_owner(box_credit_card *card, char *value){
    if (value != NULL) strncpy(card->cardOwner, value, CREDIT_CARD_OWNER_SIZE);

    return card->cardOwner;
}