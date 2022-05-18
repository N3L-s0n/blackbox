#include "stdlib.h"
#include "stdio.h"
#include "testg.h"

int main(void){

    box_http *http = box_new_http("../html/testg.html", NULL);

    box_http_content(http,2, TEXT_HTML,CHARSET_UTF_8);

    box_http_send(http);

    char *user = box_query_param(http,"username");
    char *pass= box_query_param(http,"password");

    printf("El usuario es %s",user);
    box_http_redirect(http,"..html/testg.html");
    box_destroy_http(http);

    return 0; 
    /*
    printf("Content-Type: text/html; charset=utf-8\r\nSet-Cookie: Hello, Cookie here!\r\n\r\n");
    printf("<h2>Hellow World</h3>");
    char *cookie = getenv("HTTP_COOKIE");
    if (cookie){
        printf("The cookie is: <b>%s<b><br>", cookie);
    }else{
        printf("Theres is no cookie!");
    }
    return 0; 
    
    gcc -o bin/cookie.cgi  src/core/testCookie.c src/http/box_http.c src/http/box_headers.c  src/html/box_html.c src/html/box_reader.c src/html/box_tags.c src/utils/box_regex.c src/mem/box_array.c src/mem/box_map.c src/mem/box_ntree.c
    */
}