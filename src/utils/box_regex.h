#ifndef BOX_REGEX_H
#define BOX_REGEX_H

#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MATCH 0

/* Some useful expressions */

#define EMPTY_STRING    "^([ \t\n\r\f\v]*)$"

#define AFTER_TAG       "<[^>]+>(.*)"

#define GENERIC_TAG     "([ \t\n\r\f\v]*<[^>]+>[ \t\n\r\f\v]*)"

#define VOID_TAG        "(<[^>]+/>)"

#define DOCTYPE         "(<!DOCTYPE[^>]+>)"

#define TAG_BODY        "([^<>]*)<[^>]+>"

#define END_TAG         "(</[^>]+>)"

#define TAG_NAME        "<([a-zA-Z0-9]+).*>"

#define TAG_CLASS       "<.*[ \t\n\r\f\v]class=\"([a-zA-Z0-9_]+)\".*>"

#define TAG_ID          "<.*[ \t\n\r\f\v]id=\"([a-zA-Z0-9_]+)\".*>"

#define ENDS_WITH_TAG   "<[^<]*>[ \t\n\t\f\v]*$"

#define VARIABLE_NAME   "\$\((.*)\)"

#define VAR_NAME        "([^=&]*)=[^=&]*"

#define VAR_VALUE       "[^=&]*=([^=&]*)"

#define IF_LOGGED       "(<!--[ \t\r\f\v]*@iflogged[ \t\r\f\v]*-->[ \t\n\r\f\v]*)"

#define AFTER_LOGGED    "<!--[ \t\r\f\v]*@iflogged[ \t\r\f\v]*-->(.*)"

#define IF_NOT_LOGGED   "(<!--[ \t\r\f\v]*@ifnlogged[ \t\r\f\v]*-->[ \t\n\r\f\v]*)"

#define AFTER_N_LOGGED  "<!--[ \t\r\f\v]*@ifnlogged[ \t\r\f\v]*-->(.*)"

#define COMPONENT       "<!--[ \t\r\f\v]*@component=\"([^\"]*)\"[ \t\r\f\v]*-->"

#define AFTER_COMMENT   "<!--[^(-->)]*-->(.*)"

#define ALPHA_NUMERIC   "^([a-zA-Z0-9 ]+)$"

#define NUMERIC         "^([0-9]+)$"

/* BOTH regex functions work with 0 or 1 subexpressions */

/* if you want to move string to match */
extern char *box_move_regex_match(char *string, const char *expr);

/* if you want new string with match */
extern char *box_get_regex_match(const char *string, const char *expr);

/* if you want to know if there is a match */
extern int   box_check_regex_match(const char *string, const char *expr);

/* if you want to replace variables 
 * Variables: varname1=var1&varname2=var2&...
 * Target: text with $(varname1) and $(varname2) variables 
 */
extern char *box_replace_variables(char *variables, char *target);

extern char *box_replace_regex_match(const char *vars, const char *string);

extern char *box_concat_n_destroy(char *dest, char *src);

extern char *box_copy_string(const char *src);

/*Return 0 if strings are the same*/
extern int box_same_string(char * string, char* string2);
/*Replace a pattern in a string*/
extern char * box_replace_string(char *str,char * pattern, char * replace);
/*Separate string into three pieces*/
extern char ** box_strtok_string(char * string, char * separator);

#endif

