#ifndef BOX_CREDIT_CARD_H
#define BOX_CREDIT_CARD_H


#include <string.h>
#include <stdlib.h>

#define CREDIT_CARD_NUMBER_SIZE 20
#define CREDIT_CARD_EXP_DATE_SIZE 10
#define CREDIT_CARD_OWNER_SIZE 200

typedef struct box_credit_card box_credit_card;

extern box_credit_card *box_credit_card_new(void);
extern box_credit_card *box_credit_card_fill(int id, char* number, char* date, int csv, char* owner);
extern void box_destroy_credit_card(box_credit_card *card);

extern int box_credit_card_cart_id(box_credit_card *card, int value);
extern char *box_credit_card_number(box_credit_card *card, char *value);
extern char *box_credit_card_expiration_date(box_credit_card *card, char *value);
extern int box_credit_card_csv(box_credit_card *card, int value);
extern char *box_credit_card_owner(box_credit_card *card, char *value);




#endif