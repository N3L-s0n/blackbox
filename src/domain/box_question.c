#include "box_question.h"

typedef struct box_question
{
    char email[QUESTION_EMAIL_SIZE + 1];
    char date[QUESTION_DATE_SIZE + 1];
    char subject[QUESTION_SUBJECT_SIZE + 1];
    char description[QUESTION_DESCRIPTION_SIZE + 1]
} box_question;

extern box_question *box_question_new(void){
    box_question *question = (box_question *)calloc(1, sizeof(box_question));
    return question;
}

extern box_question *box_question_fill(char* email, char* subject, char* description){
    
    char date[QUESTION_DATE_SIZE] = {0};
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);
    strftime(date, 15, "%Y-%m-%d", ptm);
    
    if (email == NULL || date == NULL) return NULL;
    
    box_question* question = (box_question *)calloc(1, sizeof(box_question));
    
    if (email != NULL) strncpy(question->email, email, QUESTION_EMAIL_SIZE);
    if (date != NULL) strncpy(question->date, date, QUESTION_DATE_SIZE);
    if (subject != NULL) strncpy(question->subject, subject, QUESTION_SUBJECT_SIZE);
    if (description != NULL) strncpy(question->description, description, QUESTION_DESCRIPTION_SIZE);
    
    return question;
}

extern void box_destroy_question(box_question* question){
    if (question != NULL) free(question);
}

extern char *box_question_email(box_question* question, char* value){
    if (value != NULL) strncpy(question->email, value, QUESTION_EMAIL_SIZE);
    return question->email;
}

extern char *box_question_date(box_question* question, char* value){
    if (value != NULL) strncpy(question->date, value, QUESTION_DATE_SIZE);
    return question->date;
}

extern char *box_question_subject(box_question* question, char* value){
    if (value != NULL) strncpy(question->subject, value, QUESTION_SUBJECT_SIZE);
    return question->subject;
}

extern char *box_question_description(box_question* question, char* value){
    if (value != NULL) strncpy(question->description, value, QUESTION_DESCRIPTION_SIZE);
    return question->description;
}