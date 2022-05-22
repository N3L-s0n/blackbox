#include "data.h"

typedef struct user
{
    char* email;
    char* name;
    char* firstLastName;
    char* secondLastName;
    char* password;
    char* address;
    char* phone;
    char* token;
};

typedef struct cart{
    int id;
    char* payDate;
    char* userEmail;
};

typedef struct CreditCard
{
    int id;
    char* cardNumber;
    char* expirationDate;
    char* CSV;
};


typedef struct product
{
    int id;
    char* name;
    int price;
    bool stock;
    char* description;
    char* imagePath;
};

typedef struct questions{
    char* email;
    char* date;
    char* subject;
    char* description;
};

typedef struct productIsINCart{
    int productId;
    int CartId;
};

/*int main()
{
    innit();
    getAllProducts();

    int numProducts = getNumberOfProducts();
    struct product *listOfProducts = (struct product *)malloc(sizeof(struct product) * numProducts);
    listOfProducts = getAllProducts();

    for (int i = 0; i < numProducts; i++)
    {
        printf("%i %s %i %i %s %s\n", listOfProducts[i].id, listOfProducts[i].name, listOfProducts[i].price, 
        listOfProducts[i].stock, listOfProducts[i].description,listOfProducts[i].imagePath);
    }

    createNewUser("a@gmail.com","name", "apellido1", "apellido2", "afdaf", "CR", "88839208", "token");

    printf("%i\n",validatePassword("a@gmail.com","afdaf"));


    listOfProducts = getProductsFilteredByName("blue");

    for (int i = 0; i < 1; i++) //cambiar num
    {
        printf("%i %s %i %i %s %s\n", listOfProducts[i].id, listOfProducts[i].name, listOfProducts[i].price, 
        listOfProducts[i].stock, listOfProducts[i].description,listOfProducts[i].imagePath);
    }

    saveQuestion("a","2022-05-14","c","d");

    createCart("joe.doe@gmail.com","123456598");

    addProduct("Red box", 300, 1, "A red box vwery pretty", "path");

    mysql_close(connection);
    free(listOfProducts);
}*/

extern void innit()
{
    connection = mysql_init(NULL);

    if (connection == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(connection));
        exit(1);
    }

    if (mysql_real_connect(connection, "localhost", "blackbox", "2uwejs45KSdf8!4$", "blackboxDB", 0, NULL, 0) == NULL)
    {
        finish_with_error(connection);
    }
}

extern void closeConnection(){
    mysql_close(connection);
}

extern void finish_with_error(MYSQL *conn)
{
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}


extern struct product *getAllProducts()
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    uint64_t rows;
    uint64_t fields;
    int i = 0;

    if (mysql_query(connection, "SELECT * FROM Product"))
    {
        finish_with_error(connection);
    }

    result = mysql_store_result(connection);

    if (result == NULL)
    {
        finish_with_error(connection);
    }

    rows = mysql_num_rows(result);
    fields = mysql_num_fields(result);

    struct product *listOfProducts = (struct product *)malloc(sizeof(struct product) * rows);

    while ((row = mysql_fetch_row(result)))
    {
        listOfProducts[i].id = atoi(box_copy_string(row[0]));
        listOfProducts[i].name = box_copy_string(row[1]);
        listOfProducts[i].price = atoi(box_copy_string(row[2]));
        listOfProducts[i].stock = atoi(box_copy_string(row[3]));
        listOfProducts[i].description = box_copy_string(row[4]);
        listOfProducts[i].imagePath = box_copy_string(row[5]);
        i++;
    }
    return listOfProducts;
}

extern int getNumberOfProducts()
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    int number = 0;

    if (mysql_query(connection, "SELECT COUNT(*) FROM Product"))
    {
        finish_with_error(connection);
    }

    result = mysql_store_result(connection);

    if (result == NULL)
    {
        finish_with_error(connection);
    }

    if (row = mysql_fetch_row(result))
    {
        number = atoi(row[0]);
    }
    return number;
}

extern struct product* getProductsFilteredByName(char* name){
    MYSQL_RES *result;
    MYSQL_ROW row;
    uint64_t rows;
    uint64_t fields;
    int i = 0;
    char* query;
    char* c = "%";
    asprintf(&query, "SELECT * from Product where Name LIKE '%s%s%s'", c, name, c);

    if (mysql_query(connection, query))
    {
        finish_with_error(connection);
    }

    result = mysql_store_result(connection);

    if (result == NULL)
    {
        finish_with_error(connection);
    }

    rows = mysql_num_rows(result);
    fields = mysql_num_fields(result);

    struct product *listOfProducts = (struct product *)malloc(sizeof(struct product) * rows);

    while ((row = mysql_fetch_row(result)))
    {
        listOfProducts[i].id = atoi(box_copy_string(row[0]));
        listOfProducts[i].name = box_copy_string(row[1]);
        listOfProducts[i].price = atoi(box_copy_string(row[2]));
        listOfProducts[i].stock = atoi(box_copy_string(row[3]));
        listOfProducts[i].description = box_copy_string(row[4]);
        listOfProducts[i].imagePath = box_copy_string(row[5]);
        i++;
    }
    return listOfProducts;

}


extern void addProduct(char* name, int price, int stock, char* description, char* image){
    char* query;
    asprintf(&query, "INSERT INTO Product (Name, Price, Stock, Description, Image) VALUES('%s','%i','%i','%s','%s')",name, price, stock, description,image);
    if (mysql_query(connection, query)) {
        finish_with_error(connection);
    }
}


extern void createNewUser(char* email, char* name, char* firstLastName, char* secondLastName, char* password, char* address, char* phone, char* token){
    char* query;
    asprintf(&query, "INSERT INTO User VALUES('%s','%s','%s','%s','%s','%s','%s','%s')", email, name, firstLastName, secondLastName, password, address, phone, token);

    if (mysql_query(connection, query)) {
        finish_with_error(connection);
    }
}

extern bool validatePassword(char* email, char* password){
    char* query;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int number = 0;
    bool pass = false;

    asprintf(&query, "SELECT Password from User where Email = '%s'",email);

    if (mysql_query(connection, query))
    {
        finish_with_error(connection);
    }

    result = mysql_store_result(connection);

    if (result == NULL)
    {
        finish_with_error(connection);
    }

    if(row = mysql_fetch_row(result)){
        if(row[0] = password){
            pass = true;
        }
    }
    return pass;

}


extern void saveQuestion(char* email, char* date, char* subject, char* description){
    char* query;
    asprintf(&query, "INSERT INTO Questions VALUES('%s','%s','%s','%s')", email, date, subject, description);
    if (mysql_query(connection, query)) {
        finish_with_error(connection);
    }

}

extern void createCart(char* email){
    char date[15] = {0};
    char* query;
    time_t rawtime = time(NULL);
    struct tm *ptm = localtime(&rawtime);
    strftime(date, 15, "%Y-%m-%d", ptm);
    asprintf(&query, "INSERT INTO Cart (PayDate, UserEmail) VALUES ('%s','%s')",date,email);
    if (mysql_query(connection, query)) {
        finish_with_error(connection);
    }
}




