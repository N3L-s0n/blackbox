#include "box_product.h"

typedef struct box_product {
    
    int id; // KEY
    int price;
    int stock;

    char name [PRODUCT_NAME_SIZE + 1];
    char description [PRODUCT_DESCRIPTION_SIZE + 1];
    char image [PRODUCT_IMAGE_SIZE + 1];

} box_product;

typedef struct box_products {
    
    box_product **products;
    size_t size;
    
} box_products;

extern box_product *box_product_new(void) {
    
    box_product *product = (box_product *)calloc(1, sizeof(box_product));

    return product;
}

extern box_products *box_products_new(size_t size) {

    if (size <= 0) return NULL;

    box_products* products = (box_products *)calloc(1, sizeof(box_products));
    products->products = (box_product **)calloc(size, sizeof(box_product *));
    products->size = size;
    
    return products;
}

extern box_product *box_product_fill(int id, char *name, int price, int stock, char *description, char *image){

    if (id < 0) return NULL; // key
        
    box_product *product = (box_product *)calloc(1, sizeof(box_product));


    product->id = id;
    product->price = price;
    product->stock = stock;

    if (name != NULL) strncpy(product->name, name, PRODUCT_NAME_SIZE);
    if (image != NULL) strncpy(product->image, image, PRODUCT_IMAGE_SIZE);
    if (description != NULL) strncpy(product->description, description, PRODUCT_DESCRIPTION_SIZE);

    return product;
    
}

extern void box_destroy_product(box_product *product){

    if (product != NULL) free(product);
}

extern void box_destroy_products(box_products *products) {
    
    if (products != NULL) {
        for (int i = 0; i < products->size; ++i) {

            box_destroy_product(products->products[i]);
        }

        free(products->products);
        free(products);
    }

}

extern box_product *box_get_product_from_array(box_products *products, unsigned int index) {

    if (products == NULL) return NULL;

    if (index >= 0 && index < products->size) return products->products[index];

    return NULL;
}

extern void box_set_product_from_array(box_products *products, box_product *product, unsigned int index) {

    if (products != NULL && product != NULL && index >= 0 && index < products->size)
        products->products[index] = product;
}

extern int box_get_product_array_size(box_products *products) {
    
    if (products != NULL) return products->size;
}

/* KEY */
extern int box_product_id(box_product *product) {

    return product->id;
}

extern char *box_product_name(box_product *product, char *value) {

    if (value != NULL) strncpy(product->name, value, PRODUCT_NAME_SIZE);

    return product->name;
}
extern char *box_product_description(box_product *product, char *value) {

    if (value != NULL) strncpy(product->description, value, PRODUCT_DESCRIPTION_SIZE);

    return product->description;
}
extern char *box_product_image(box_product *product, char *value) {

    if (value != NULL) strncpy(product->image, value, PRODUCT_IMAGE_SIZE);

    return product->image;
}

extern int   box_product_price(box_product *product, int value) {
    
    if (value > 0) product->price = value;

    return product->price;
}
extern int   box_product_stock(box_product *product, int value) {

    if (value > 0) product->stock = value;

    return product->stock;
}
