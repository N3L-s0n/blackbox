#include "../http/box_http.h"

int main(int argc, char **argv, char **env){
    
    box_http *http = box_new_http("../html/index.html", env);
    box_http_content(http, 2, TEXT_HTML, CHARSET_UTF_8);

    box_set_class_variables(http, "subheader", "subtitle=Aiming for secure.", 0);
    
    box_send_headers(http);
    box_send_html(http);

    box_destroy_http(http);
    return 0;
}
