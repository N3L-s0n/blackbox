#include "box_url.h"

static int ishex(int x)
{
	return	(x >= '0' && x <= '9')	||
		(x >= 'a' && x <= 'f')	||
		(x >= 'A' && x <= 'F');
}
 
extern char *box_url_decode(const char *url)
{
    char *string = (char *)calloc(strlen(url)+1, sizeof(url));

	char *o;
	const char *end = url + strlen(url);
	int c;
 
	for (o = string; url <= end; o++) {
		c = *url++;
		if (c == '+') c = ' ';
		else if (c == '%' && (	!ishex(*url++)	||
					!ishex(*url++)	||
					!sscanf(url - 2, "%2x", &c)))
			return NULL;
 
		if (string) *o = c;
	}
 
	return string;
}
