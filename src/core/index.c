#include "../http/box_http.h"

int main(void){
    
    box_http *http = box_new_http("html/index.html", NULL);

    box_http_content(http, 2, TEXT_HTML, CHARSET_UTF_8);
    
    box_http_send(http);

    box_destroy_http(http);

    return 0;
}
