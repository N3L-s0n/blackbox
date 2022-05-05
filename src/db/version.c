#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

void finish_with_error (MYSQL *conn){
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

int main( void ){
    printf( "MySQL client version: %s\n", mysql_get_client_info() );

    MYSQL *connection = mysql_init(NULL);
    MYSQL_RES *result;
    MYSQL_ROW row;

    uint64_t rows;
    uint64_t fields;
    
    if (connection == NULL) {
        fprintf(stderr, "%s\n", mysql_error(connection));
        exit(1);
    }

    if (mysql_real_connect( connection, "localhost", "blackbox", "2uwejs45KSdf8!4$", "prueba", 0, NULL, 0 ) == NULL) {
        finish_with_error( connection );
    }

    if (mysql_query( connection, "SELECT * FROM pet")) {
        finish_with_error( connection );
    }
    
    result = mysql_store_result(connection);

    if (result == NULL ){
        finish_with_error(connection);
    }

    rows = mysql_num_rows(result);
    fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result))){

        for (int i = 0; i < fields; ++i){
            printf("%s ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }

    return 0;
}
