#ifndef BOX_QUESTION_H
#define BOX_QUESTION_H

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../utils/box_entry_validation.h"

#define QUESTION_EMAIL_SIZE 100
#define QUESTION_DATE_SIZE 20
#define QUESTION_SUBJECT_SIZE 200
#define QUESTION_DESCRIPTION_SIZE 300

typedef struct box_question box_question;

extern box_question *box_question_new(void);
extern box_question *box_question_fill(char* email, char* subject, char* description);
extern void box_destroy_question(box_question* question);

extern char *box_question_email(box_question* question, char* value); 
extern char *box_question_date(box_question* question, char* value); 
extern char *box_question_subject(box_question* question, char* value); 
extern char *box_question_description(box_question* question, char* value); 

#endif