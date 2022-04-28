#include "blackbox.h"

int main(void){
   
    int values [] = {BOX_TYPE_TEXT_HTML, BOX_TYPE_CHARSET_UTF};

    
    box_print_content_type(values, 2);
    printf("\r\n");

    printf("<h1>BLACKBOX</h1>");

    return 0;
}
