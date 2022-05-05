#include "blackbox.h"

int main(void){

    box_headers *headers;

    box_type_values type_values[] = {TEXT_HTML, CHARSET_UTF_8};

    headers = box_new_headers();

    box_header_add_content_type(headers, type_values, 2);
    
    box_print_headers(headers);

    box_file index = box_read_file("../html/index.html");

    box_html_print_document(index);

    box_destroy_file(index);
    box_destroy_headers(headers);

    return 0;
}
