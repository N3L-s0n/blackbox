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

#define TAG_BODY        "([^<>]*)</[^>]+>"

#define END_TAG         "(</[^>]+>)"

#define TAG_NAME        "<([a-zA-Z0-9]+).*>"

#define TAG_CLASS       "<.*[ \t\n\r\f\v]class=\"([a-zA-Z0-9_]+)\".*>"

#define TAG_ID          "<.*[ \t\n\r\f\v]id=\"([a-zA-Z0-9_]+)\".*>"

#define ENDS_WITH_TAG   "<[^<]*>[ \t\n\t\f\v]*$"

#define VARIABLE_NAME   "\$\((.*)\)"


/* BOTH regex functions work with 0 or 1 subexpressions */

/* if you want to move string to match */
extern char *box_move_regex_match(char *string, const char *expr);

/* if you want new string with match */
extern char *box_get_regex_match(const char *string, const char *expr);

/* if you want to know if there is a match */
extern int   box_check_regex_match(const char *string, const char *expr);

extern char *box_concat_n_destroy(char *dest, char *src);

extern char *box_copy_string(const char *src);

#endif

