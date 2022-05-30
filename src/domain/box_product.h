#ifndef BOX_PRODUCT_H
#define BOX_PRODUCT_H

#include <string.h>
#include <stdlib.h>

#include "../mem/box_array.h"

#define PRODUCT_NAME_SIZE 200
#define PRODUCT_DESCRIPTION_SIZE 300
#define PRODUCT_IMAGE_SIZE 100

typedef struct box_product box_product;
typedef struct box_products box_products;

extern box_product *box_product_new(void);

extern box_products *box_products_new(size_t size);

extern box_product *box_product_copy(box_product *orignal);

extern box_product *box_product_fill(int id, char *name, int price, int stock, char *description, char *image);

extern void box_destroy_product(box_product *product);

extern void box_destroy_products(box_products *products);

extern box_product *box_get_product_from_array(box_products *products, unsigned int index);
extern int box_get_product_array_size(box_products *products);
extern void box_set_product_from_array(box_products *products, box_product *product, unsigned int index);
extern void box_products_add(box_products *products, box_product *product);

extern box_products *box_products_diff(box_products *original, box_products *updated);

extern int box_get_products_total(box_products *products);

/* KEY */
extern int box_product_id(box_product *product);

extern char *box_product_name(box_product *product, char *value);
extern int   box_product_price(box_product *product, int value);
extern int   box_product_stock(box_product *product, int value);
extern char *box_product_description(box_product *product, char *value);
extern char *box_product_image(box_product *product, char *value);

#endif
